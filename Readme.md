# Mohanad Mohamed - Embedded Software Engineer

## Final Project Repository Details
You can find the final project in the `ITIDA/Final-Project` branch.

### Project Components
- `server_json`: The server application.
- `client_json`: The client console application.
- `clientGUI`: The client widget application.

### Email Notification
I've implemented `send_email.py` to send real emails whenever a transaction occurs. It's executed from the server application.

### Backup with bashScript.sh
I use `bashScript.sh` for database backup, pushing it to the repository whenever I send a `kill -15` signal and every 24 hours.

### Server Control with serverService.sh
I've employed `serverService.sh` to connect with `qt_server.service` for controlling the server executable, ensuring its availability.

### PlantUML Sequence Diagram
I've created a sequence diagram using PlantUML to visualize the interactions in the system.

**Note:** If you intend to use any of the bash features, ensure that you correct the necessary paths.
