import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
import sys

if len(sys.argv) != 3:
    print("Usage: python script.py <recipient_email> <message_body>")
    sys.exit(1)

sender_email = "mohanadmohamed202100@gmail.com"
sender_password = "fehl bvdm gcpo mmtx"

recipient_email = sys.argv[1]
message_body = sys.argv[2]

message = MIMEMultipart()
message["From"] = sender_email
message["To"] = recipient_email
message["Subject"] = "Bank System"
body = message_body
message.attach(MIMEText(body, "plain"))

smtp_server = "smtp.gmail.com"
smtp_port = 587

try:
    with smtplib.SMTP(smtp_server, smtp_port) as server:
        server.starttls()
        server.login(sender_email, sender_password)
        server.sendmail(sender_email, recipient_email, message.as_string())
    print("Email sent successfully.")
except Exception as e:
    print(f"An error occurred: {e}")
