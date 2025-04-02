from sqlalchemy import create_engine, Column, Integer, String, Enum, Boolean
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker
from enum import Enum as PyEnum

# Define database URL and engine
DATABASE_URL = "sqlite:///./test.db"
engine = create_engine(DATABASE_URL, connect_args={"check_same_thread": False})
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

# Define base for models
Base = declarative_base()


# Lead States
class LeadState(PyEnum):
    PENDING = "PENDING"
    REACHED_OUT = "REACHED_OUT"


# Lead format
class Lead(Base):
    __tablename__ = 'leads'
    id = Column(Integer, primary_key=True, index=True)
    first_name = Column(String, index=True)
    last_name = Column(String, index=True)
    email = Column(String, unique=True, index=True)
    resume = Column(String)
    state = Column(Enum(LeadState), default=LeadState.PENDING)


# User format
class User(Base):
    __tablename__ = "users"

    id = Column(Integer, primary_key=True, index=True)
    username = Column(String, unique=True, index=True)
    password_hash = Column(String)
    is_active = Column(Boolean, default=True)  # Can be used to mark if the user is active or not


# Create all tables in the database
Base.metadata.create_all(bind=engine)
