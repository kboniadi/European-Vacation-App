import sqlite3
import csv
import sys

def ImportCityTemplate(filename):
    # conn = sqlite3.connect('Data.db')
    # conn.execute("PRAGMA foreign_keys=1")
    # cur = conn.cursor()    

    cur.execute("CREATE TABLE IF NOT EXISTS cities(id INTEGER PRIMARY KEY AUTOINCREMENT, cityNames TEXT)")

    with open(filename, 'r') as csvFile:
        readCSV = csv.reader(csvFile, delimiter=',')
        
        for row in readCSV:
            cur.execute("INSERT INTO cities(cityNames) VALUES(?)", row)
    # conn.commit()
    # cur.close()
    # conn.close()


def ImportFile(filename, table, column1, column2):
    # conn = sqlite3.connect("Data.db")
    # cur = conn.cursor()

    cur.execute('SELECT * FROM cities')
    outer = cur.fetchall()

    temp = '''CREATE TABLE IF NOT EXISTS {0}(id INTEGER, {1} TEXT,
    {2} INTEGER, FOREIGN KEY(id) REFERENCES cities(id) ON DELETE CASCADE)'''.format(table, column1, column2)
    cur.execute(temp)

    with open(filename, 'r') as csvFile:
        readCSV = csv.reader(csvFile, delimiter=',')
        # cur.executemany("INSERT INTO "+table+"(startcity, endcity, distance) VALUES(?, ?, ?)", readCSV)

        line_list = list(readCSV)

        temp2 = "INSERT INTO {0}(id, {1}, {2}) VALUES(?, ?, ?)".format(table, column1, column2)
        
        count = 1
        i = 0
        for index in outer:
            while i < len(line_list):
                if index[1] == line_list[i][0]:
                    cur.execute(temp2, (count, line_list[i][1], line_list[i][2]))
                    i += 1
                else:
                    count += 1
                    break

    # conn.commit()
    # cur.close()
    # conn.close()

def ImportAccounts(username, password, accessLevel):
    cur.execute("CREATE TABLE IF NOT EXISTS accounts(username TEXT, password TEXT, level TEXT)");
    cur.execute("INSERT INTO accounts(username, password, level) VALUES(?, ?, ?)", (username, password, accessLevel));

# def getData():
#     con = sqlite3.connect('Data.db')
 
#     with con:

#         cur = con.cursor()
#         cur.execute("SELECT * FROM Food")
        
#         for row in cur.fetchall():
#             print(row[0], row[1], row[2])



def DropTable(tableName):
    # conn = sqlite3.connect('Data.db')
    # cur = conn.cursor()

    temp = "DROP TABLE IF EXISTS {0}".format(tableName)
    cur.execute(temp)
    # conn.commit()


if __name__ == "__main__":
    conn = sqlite3.connect('Data.db')
    conn.execute("PRAGMA foreign_keys=1")
    cur = conn.cursor()

    DropTable('distance')
    DropTable('food')
    DropTable('cities')
    DropTable('accounts');
    # DropTable('New_Cities')

    ImportCityTemplate('cities.csv')
    ImportFile('Dist_&_Foods-Distances.csv', 'distance', 'endCity', 'distances')
    ImportFile('Dist_&_Foods-Foods.csv', 'food', 'foodNames', 'price')
    ImportAccounts('admin', 'password', 'ADMIN');
    
    # getData()

    conn.commit()
    cur.close()
    conn.close()
