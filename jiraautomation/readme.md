#Steps to run the script:

#1. Create a Personal Access Token in Jira Profile(Profile->Personal Access Token) and replace the token in the line "Authorization": "Bearer ODE3MzI2NDY4OTgzOmNSYEOeQjx+OmvnOrrjqSzLGylu".Token is "ODE3MzI2NDY4OTgzOmNSYEOeQjx+OmvnOrrjqSzLGylu".You can refer the JIRA rest api's in https://docs.atlassian.com/software/jira/docs/api/REST/7.6.1/
#2. Run the script and enter the branch name and last commit ID.

#3. The script will clone the repositories and create a file with the ticket names

#4. The script will make an API call to Jira for each ticket name and get the status, summary, assignee name, and email.

#5. The script will write the ticket details to an Excel file.

#6. The script will merge all the seperate excel files into a single excel file,which may contain the conflicts of the ticket details as two or more repositories may have the same ticket.

