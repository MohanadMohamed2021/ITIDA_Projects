#i/bin/bash

git fetch origin ITIDA/Final-Project

git chechout ITIDA/Final-Project

cp ~/server_json/DataBase.json  .
cp ~/server_json/Transaction_DataBase.json  .

git add DataBase.json Transaction_DataBase.json

git commit -m "Updated Data-Base"

git push origin ITIDA/Final-Project

