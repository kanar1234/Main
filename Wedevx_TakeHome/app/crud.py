from sqlalchemy.orm import Session
from . import models, schemas


# Where create, read, update, and delete operations happen
def create_lead(db: Session, lead: schemas.LeadCreate):
    db_lead = models.Lead(**lead.dict())
    db.add(db_lead)
    db.commit()
    db.refresh(db_lead)
    return db_lead


def get_leads(db: Session):
    return db.query(models.Lead).all()


def update_lead_state(db: Session, lead_id: int, state: models.LeadState):
    db_lead = db.query(models.Lead).filter(models.Lead.id == lead_id).first()
    if db_lead:
        db_lead.state = state
        db.commit()
        db.refresh(db_lead)
        return db_lead
    return None


def get_user_by_username(db: Session, username: str):
    return db.query(models.User).filter(models.User.username == username).first()
