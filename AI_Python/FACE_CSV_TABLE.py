import sqlite3      
import csv  

conn = sqlite3.connect('/home/cat/closed_loop_system/build-cls-Qt_5_15_8_qt5-Debug/mydatabase.db')  
cursor = conn.cursor()  

cursor.execute("SELECT * FROM FACE_TABLE")     
rows = cursor.fetchall()  

with open('FACE_TABLE.csv', 'w', newline='', encoding='utf-8' ) as file:  
    writer = csv.writer(file)  
    writer.writerow([i[0] for i in cursor.description]) # write headers  
    writer.writerows(rows) # write data rows    
    
    conn.close()    

print("CSV file created successfully.");    
