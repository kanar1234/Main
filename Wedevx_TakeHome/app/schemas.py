from pydantic import BaseModel
from enum import Enum


class LeadState(str, Enum):
    PENDING = "PENDING"
    REACHED_OUT = "REACHED_OUT"


class LeadCreate(BaseModel):
    first_name: str
    last_name: str
    email: str
    resume: str


class LeadOut(BaseModel):
    id: int
    first_name: str
    last_name: str
    email: str
    resume: str
    state: LeadState

    # Allows mapping from OOP to databases
    class Config:
        orm_mode = True


class UserCreate(BaseModel):
    username: str
    password: str


class UserOut(BaseModel):
    id: int
    username: str
    is_active: bool

