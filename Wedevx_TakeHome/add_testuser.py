from sqlalchemy.orm import Session
from app.database import SessionLocal
from app.models import User
from app.pwd_utils import hash_password

# Create a new database session
db = SessionLocal()

# Manually add a test user
test_username = "testuser"
test_password = "testpassword"

# Hash the password
hashed_password = hash_password(test_password)

# Create a new user instance
new_user = User(username=test_username, password_hash=hashed_password)

# Add the user to the session
db.add(new_user)

# Commit the session to save the new user to the database
db.commit()

# Close the session
db.close()

print(f"User '{test_username}' added successfully!")
