from fastapi import FastAPI, Depends, HTTPException, status
from fastapi.security import OAuth2PasswordBearer, OAuth2PasswordRequestForm
from sqlalchemy.orm import Session

from . import models, schemas, crud, auth, database, pwd_utils, auth_utils, email_utils
from .models import User
from .database import SessionLocal

app = FastAPI()


# Dependency to get the DB session
def get_db() -> Session:
    db = SessionLocal()  # Create a new session
    try:
        yield db  # This is what FastAPI expects for dependency injection
    finally:
        db.close()  # Close the session after the request is finished


# Verify User -> Returns Token
@app.post("/auth/login")
def login(form_data: OAuth2PasswordRequestForm = Depends(), db: Session = Depends(get_db)):
    user = db.query(User).filter(User.username == form_data.username).first()
    if not user or not pwd_utils.verify_password(form_data.password, user.password_hash):
        raise HTTPException(status_code=400, detail="Invalid credentials")

    token = auth_utils.create_access_token({"sub": user.username})
    return {"access_token": token, "token_type": "bearer"}


# Post Request
@app.post("/leads/", response_model=schemas.LeadOut)
def create_lead(lead: schemas.LeadCreate, db: Session = Depends(get_db),
                current_user: models.User = Depends(auth.get_current_user)):
    db_lead = crud.create_lead(db, lead)

    # Send email notifications
    email_utils.send_email(lead.email, "Lead Submitted", "Thank you for submitting your lead.")
    email_utils.send_email("attorney@example.com", "New Lead Submitted",
                           f"A new lead from {lead.first_name} {lead.last_name} has been submitted.")

    return db_lead


# Get Request
@app.get("/leads/", response_model=list[schemas.LeadOut])
def get_leads(db: Session = Depends(database.get_db),
              current_user: models.User = Depends(auth.get_current_user)):
    return crud.get_leads(db)


# Put Request
@app.put("/leads/{lead_id}/{state}", response_model=schemas.LeadOut)
def update_lead(lead_id: int, state: models.LeadState, db: Session = Depends(database.get_db),
                current_user: models.User = Depends(auth.get_current_user)):
    db_lead = crud.update_lead_state(db, lead_id, state)
    if not db_lead:
        raise HTTPException(status_code=404, detail="Lead not found")
    return db_lead
