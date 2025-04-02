import requests

# First, login to get the token
credentials = {
    "username": "testuser",
    "password": "testpassword",
    "grant_type": "password"
}

# Make a POST request to get the JWT token
response = requests.post("http://127.0.0.1:8000/auth/login", data=credentials)

# Check if the login was successful and extract the token
if response.status_code == 200:
    token = response.json()["access_token"]
    print(f"Successfully obtained token: {token}")
else:
    print(f"Failed to obtain token. Status code: {response.status_code}")
    print(response.json())  # Print response error for debugging
    exit()

# Now, use the token to make a PUT request to update a lead
lead_id = 5  # ID of the lead you want to update
state = "REACHED_OUT"  # The state to update (make sure this matches the LeadState enum)

# Prepare the headers with the JWT token
headers = {
    "Authorization": f"Bearer {token}"
}

# Make a PUT request to the FastAPI server to update the lead
# response = requests.get(f"http://127.0.0.1:8000/leads/{lead_id}/{state}", headers=headers)

# Make a GET request to the FastAPI server to update the lead
response = requests.get(f"http://127.0.0.1:8000/leads/", headers=headers)

# Check if the request was successful (status code 200)
if response.status_code == 200:
    updated_lead = response.json()  # Convert the response to JSON
    print(f"Response successful: {updated_lead}")
else:
    print(f"Failed to update lead. Status code: {response.status_code}")
    # print(response.json())  # Print response error for debugging
