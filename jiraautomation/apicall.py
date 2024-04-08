#Steps to run the script:
#1. Create a Personal Access Token in Jira Profile(Profile->Personal Access Token) and replace the token in the line "Authorization": "Bearer ODE3MzI2NDY4OTgzOmNSYEOeQjx+OmvnOrrjqSzLGylu".Token is "ODE3MzI2NDY4OTgzOmNSYEOeQjx+OmvnOrrjqSzLGylu"
#2. Run the script and enter the branch name and last commit ID.
#3. The script will clone the repositories and create a file with the ticket names
#4. The script will make an API call to Jira for each ticket name and get the status, summary, assignee name, and email.
#5. The script will write the ticket details to an Excel file.
#6. The script will merge all the seperate excel files into a single excel file,which may contain the conflicts of the ticket details as two or more repositories may have the same ticket.

import requests
import re
import pandas as pd
import subprocess
import os


# Set the Jira base URL and API endpoint
base_url = "http://ccp.sys.comcast.net/"
api_endpoint = "/rest/api/2/issue"

# Set the headers (optional)
headers = {
    "Content-Type": "application/json",
    "Authorization": "Bearer ODE3MzI2NDY4OTgzOmNSYEOeQjx+OmvnOrrjqSzLGylu"
}

repository_urls = [
    'https://code.rdkcentral.com/r/rdk/components/generic/aamp',
    'https://code.rdkcentral.com/r/rdk/components/generic/aampabr'
    'https://code.rdkcentral.com/r/rdk/components/generic/gst-plugins-rdk-aamp',
    'https://code.rdkcentral.com/r/rdk/components/generic/aampmetrics',
    
]
# Create an empty DataFrame to store the merged data
merged_data = pd.DataFrame()

# Clone each repository
for url in repository_urls:
    repository_directory = 'C:\\Documents\\repositories\\' + url.split('/')[-1]
    branch = input("Enter the branch name: ")

    commit = input("Enter the last commit ID: ")
    subprocess.run(['git', 'clone', '-b', branch, url, repository_directory])
    os.chdir(repository_directory)
    with open('git_log_output.txt', 'w') as file:
        subprocess.run(['git', 'log'], stdout=file)
    ticket_names = []
    with open("git_log_output.txt", "r", encoding='utf-8') as file:
        for line in file:
            if commit in line:
                break
            match = re.search(r"\b((DELIA|RDK|RDKTV|XIONE|RDKCOM|RDKDEV|LLAMA|RDKCI|RDKSVREQ|RDKAAMP|AMLOGIC|BCOM|RDKCMF|XRE|BLDK|SERXIONE)-\d+)\b", line)
            if match:
                ticket_names.append(match.group(1))
    print(ticket_names)
    # Write the ticket names to a separate file
    with open("ticket_names.txt", "w") as file:
        for ticket_name in ticket_names:
            file.write(ticket_name + "\n")

    # Read the ticket names from the file
    with open("ticket_names.txt", "r") as file:
        ticket_ids = [line.strip() for line in file]
    # Make the API call for each ticket ID
    for ticket_id in ticket_ids:
        # Construct the API endpoint for the specific ticket ID
        ticket_api_endpoint = f"{api_endpoint}/{ticket_id}"

        # Make the API call
        response = requests.get(base_url + ticket_api_endpoint, headers=headers)

            # Check the response status code
        if response.status_code == 200:
            
            # API call successful
            data = response.json()

            status_name = data['fields'].get('status', {}).get('name')
            summary = data['fields'].get('summary')
            assignee = data['fields'].get('assignee')
            if assignee:
                assignee_name = assignee.get('displayName')
                email = assignee.get('emailAddress')
            else:
                print(f"Error for ticket ID {ticket_id}: Assignee Name and Email are missing")
                assignee_name = "Not found"
                email = "Not found"

            if status_name is None or summary is None:
                print(f"Error for ticket ID {ticket_id}: Status Name and Summary are missing")
            else:
                print(f"Ticket ID: {ticket_id}, Status Name: {status_name}, Summary: {summary}, Assignee: {assignee_name}, Email: {email}")
            try:
                existing_data = pd.read_excel('ticket_status.xlsx')
            except FileNotFoundError:
                existing_data = pd.DataFrame()

            # Create a new DataFrame with the ticket ID and status name
            new_data = pd.DataFrame({'Ticket ID': [ticket_id], 'Summary': [summary], 'Assignee': [assignee_name], 'Email': [email], 'Status Name': [status_name]})

            # Remove any existing rows with the same ticket ID from the existing data
            if 'Ticket ID' in existing_data.columns:
                existing_data = existing_data[existing_data['Ticket ID'] != ticket_id]

            # Concatenate the existing data and new data
            updated_data = pd.concat([existing_data, new_data], ignore_index=True)


            # Write the updated DataFrame to the Excel file
            updated_data.to_excel('ticket_status.xlsx', index=False, header=True)

        
        else:
            # API call failed
            print(f"Error for ticket ID {ticket_id}:", response.status_code)

            
    excel_files = [file for file in os.listdir() if file.endswith('.xlsx')]

     # Iterate over each Excel file
    for file in excel_files:
        # Read the Excel file into a DataFrame
        data = pd.read_excel(file)
                            
        # Append the data to the merged_data DataFrame
        merged_data = pd.concat([merged_data, data], ignore_index=True)

# Write the merged data to a new Excel file
merged_data.to_excel('C:\\Documents\\repositories\\merged_data.xlsx', index=False)
