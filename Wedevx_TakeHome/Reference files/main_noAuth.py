from fastapi import FastAPI, HTTPException, Depends
from sqlalchemy.orm import Session
from Wedevx_TakeHome.app.database import SessionLocal

from Wedevx_TakeHome.app import models, schemas, crud, database, email_utils

app = FastAPI()


# Dependency to get the DB session
def get_db() -> Session:
    db = SessionLocal()  # Create a new session
    try:
        yield db  # This is what FastAPI expects for dependency injection
    finally:
        db.close()  # Close the session after the request is finished


# Create a new lead
@app.post("/leads/", response_model=schemas.LeadOut)
def create_lead(lead: schemas.LeadCreate, db: Session = Depends(get_db)):
    db_lead = crud.create_lead(db, lead)

    # Send email notifications
    email_utils.send_email(lead.email, "Lead Submitted", "Thank you for submitting your lead.")
    email_utils.send_email("attorney@example.com", "New Lead Submitted",
                           f"A new lead from {lead.first_name} {lead.last_name} has been submitted.")

    return db_lead


# Retrieve all leads (internal UI)
@app.get("/leads/", response_model=list[schemas.LeadOut])
def get_leads(db: Session = Depends(get_db)):
    return crud.get_leads(db)


# Update the state of a lead (internal UI)
@app.put("/leads/{lead_id}", response_model=schemas.LeadOut)
def update_lead(lead_id: int, state: models.LeadState, db: Session = Depends(get_db)):
    db_lead = crud.update_lead_state(db, lead_id, state)
    if not db_lead:
        raise HTTPException(status_code=404, detail="Lead not found")
    return db_lead
