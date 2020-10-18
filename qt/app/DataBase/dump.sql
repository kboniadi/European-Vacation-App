PRAGMA foreign_keys=ON;
BEGIN TRANSACTION;
CREATE TABLE cities(id INTEGER PRIMARY KEY AUTOINCREMENT, cityNames TEXT);
INSERT INTO cities VALUES(1,'Amsterdam');
INSERT INTO cities VALUES(2,'Berlin');
INSERT INTO cities VALUES(3,'Brussels');
INSERT INTO cities VALUES(4,'Budapest');
INSERT INTO cities VALUES(5,'Hamburg');
INSERT INTO cities VALUES(6,'Lisbon');
INSERT INTO cities VALUES(7,'London');
INSERT INTO cities VALUES(8,'Madrid');
INSERT INTO cities VALUES(9,'Paris');
INSERT INTO cities VALUES(10,'Prague');
INSERT INTO cities VALUES(11,'Rome');
CREATE TABLE distance(id INTEGER, endCity TEXT,
    distances INTEGER, FOREIGN KEY(id) REFERENCES cities(id) ON DELETE CASCADE);
INSERT INTO distance VALUES(1,'Berlin',655);
INSERT INTO distance VALUES(1,'Brussels',236);
INSERT INTO distance VALUES(1,'Budapest',1395);
INSERT INTO distance VALUES(1,'Hamburg',361);
INSERT INTO distance VALUES(1,'Lisbon',2236);
INSERT INTO distance VALUES(1,'London',541);
INSERT INTO distance VALUES(1,'Madrid',1767);
INSERT INTO distance VALUES(1,'Paris',430);
INSERT INTO distance VALUES(1,'Prague',878);
INSERT INTO distance VALUES(1,'Rome',1647);
INSERT INTO distance VALUES(2,'Amsterdam',655);
INSERT INTO distance VALUES(2,'Brussels',765);
INSERT INTO distance VALUES(2,'Budapest',873);
INSERT INTO distance VALUES(2,'Hamburg',288);
INSERT INTO distance VALUES(2,'Lisbon',2779);
INSERT INTO distance VALUES(2,'London',678);
INSERT INTO distance VALUES(2,'Madrid',2392);
INSERT INTO distance VALUES(2,'Paris',1054);
INSERT INTO distance VALUES(2,'Prague',349);
INSERT INTO distance VALUES(2,'Rome',1502);
INSERT INTO distance VALUES(3,'Amsterdam',236);
INSERT INTO distance VALUES(3,'Berlin',765);
INSERT INTO distance VALUES(3,'Budapest',1353);
INSERT INTO distance VALUES(3,'Hamburg',489);
INSERT INTO distance VALUES(3,'Lisbon',2357);
INSERT INTO distance VALUES(3,'London',403);
INSERT INTO distance VALUES(3,'Madrid',1578);
INSERT INTO distance VALUES(3,'Paris',313);
INSERT INTO distance VALUES(3,'Prague',898);
INSERT INTO distance VALUES(3,'Rome',1483);
INSERT INTO distance VALUES(4,'Amsterdam',1395);
INSERT INTO distance VALUES(4,'Berlin',873);
INSERT INTO distance VALUES(4,'Brussels',1353);
INSERT INTO distance VALUES(4,'Hamburg',1163);
INSERT INTO distance VALUES(4,'Lisbon',3069);
INSERT INTO distance VALUES(4,'London',1707);
INSERT INTO distance VALUES(4,'Madrid',2512);
INSERT INTO distance VALUES(4,'Paris',1485);
INSERT INTO distance VALUES(4,'Prague',525);
INSERT INTO distance VALUES(4,'Rome',1274);
INSERT INTO distance VALUES(5,'Amsterdam',361);
INSERT INTO distance VALUES(5,'Berlin',288);
INSERT INTO distance VALUES(5,'Brussels',489);
INSERT INTO distance VALUES(5,'Budapest',1163);
INSERT INTO distance VALUES(5,'Lisbon',2121);
INSERT INTO distance VALUES(5,'London',930);
INSERT INTO distance VALUES(5,'Madrid',2171);
INSERT INTO distance VALUES(5,'Paris',376);
INSERT INTO distance VALUES(5,'Prague',640);
INSERT INTO distance VALUES(5,'Rome',1658);
INSERT INTO distance VALUES(6,'Amsterdam',2236);
INSERT INTO distance VALUES(6,'Berlin',2779);
INSERT INTO distance VALUES(6,'Brussels',2357);
INSERT INTO distance VALUES(6,'Budapest',3069);
INSERT INTO distance VALUES(6,'Hamburg',2121);
INSERT INTO distance VALUES(6,'London',2189);
INSERT INTO distance VALUES(6,'Madrid',625);
INSERT INTO distance VALUES(6,'Paris',1736);
INSERT INTO distance VALUES(6,'Prague',2707);
INSERT INTO distance VALUES(6,'Rome',2510);
INSERT INTO distance VALUES(7,'Amsterdam',541);
INSERT INTO distance VALUES(7,'Berlin',678);
INSERT INTO distance VALUES(7,'Brussels',403);
INSERT INTO distance VALUES(7,'Budapest',1707);
INSERT INTO distance VALUES(7,'Hamburg',930);
INSERT INTO distance VALUES(7,'Lisbon',2189);
INSERT INTO distance VALUES(7,'Madrid',1719);
INSERT INTO distance VALUES(7,'Paris',464);
INSERT INTO distance VALUES(7,'Prague',1265);
INSERT INTO distance VALUES(7,'Rome',1866);
INSERT INTO distance VALUES(8,'Amsterdam',1767);
INSERT INTO distance VALUES(8,'Berlin',2392);
INSERT INTO distance VALUES(8,'Brussels',1578);
INSERT INTO distance VALUES(8,'Budapest',2512);
INSERT INTO distance VALUES(8,'Hamburg',2171);
INSERT INTO distance VALUES(8,'Lisbon',625);
INSERT INTO distance VALUES(8,'London',1719);
INSERT INTO distance VALUES(8,'Paris',1633);
INSERT INTO distance VALUES(8,'Prague',2312);
INSERT INTO distance VALUES(8,'Rome',1951);
INSERT INTO distance VALUES(9,'Amsterdam',430);
INSERT INTO distance VALUES(9,'Berlin',1054);
INSERT INTO distance VALUES(9,'Brussels',313);
INSERT INTO distance VALUES(9,'Budapest',1485);
INSERT INTO distance VALUES(9,'Hamburg',376);
INSERT INTO distance VALUES(9,'Lisbon',1736);
INSERT INTO distance VALUES(9,'London',464);
INSERT INTO distance VALUES(9,'Madrid',1633);
INSERT INTO distance VALUES(9,'Prague',1030);
INSERT INTO distance VALUES(9,'Rome',1442);
INSERT INTO distance VALUES(10,'Amsterdam',878);
INSERT INTO distance VALUES(10,'Berlin',349);
INSERT INTO distance VALUES(10,'Brussels',898);
INSERT INTO distance VALUES(10,'Budapest',525);
INSERT INTO distance VALUES(10,'Hamburg',640);
INSERT INTO distance VALUES(10,'Lisbon',2707);
INSERT INTO distance VALUES(10,'London',1265);
INSERT INTO distance VALUES(10,'Madrid',2312);
INSERT INTO distance VALUES(10,'Paris',1030);
INSERT INTO distance VALUES(10,'Rome',1303);
INSERT INTO distance VALUES(11,'Amsterdam',1647);
INSERT INTO distance VALUES(11,'Berlin',1502);
INSERT INTO distance VALUES(11,'Brussels',1483);
INSERT INTO distance VALUES(11,'Budapest',1274);
INSERT INTO distance VALUES(11,'Hamburg',1658);
INSERT INTO distance VALUES(11,'Lisbon',2510);
INSERT INTO distance VALUES(11,'London',1866);
INSERT INTO distance VALUES(11,'Madrid',1951);
INSERT INTO distance VALUES(11,'Paris',1442);
INSERT INTO distance VALUES(11,'Prague',1303);
CREATE TABLE food(id INTEGER, foodNames TEXT,
    price INTEGER, FOREIGN KEY(id) REFERENCES cities(id) ON DELETE CASCADE);
INSERT INTO food VALUES(1,'Stroopwafel',5.7599999999999997868);
INSERT INTO food VALUES(1,'Thick Dutch fries',3.2099999999999999644);
INSERT INTO food VALUES(1,'Kibbeling',8.6500000000000003552);
INSERT INTO food VALUES(2,'Pretzels',4);
INSERT INTO food VALUES(2,'Apfelstrudel',6.25);
INSERT INTO food VALUES(2,'Berliner Pfannkuche',8.2300000000000004263);
INSERT INTO food VALUES(2,'Schnitzel',9.7899999999999991473);
INSERT INTO food VALUES(3,'Waterzooi',6.4500000000000001776);
INSERT INTO food VALUES(3,'Luikse Siroop',4.9800000000000004263);
INSERT INTO food VALUES(3,'Mosselen-friet',4.4500000000000001776);
INSERT INTO food VALUES(3,'Speculoos',2.7900000000000000355);
INSERT INTO food VALUES(4,'goulash',8.4299999999999997157);
INSERT INTO food VALUES(4,'Stuffed cabbage',6.9900000000000002131);
INSERT INTO food VALUES(4,'Smoked meat',12.990000000000000212);
INSERT INTO food VALUES(4,'Dobos torta',2.7900000000000000355);
INSERT INTO food VALUES(5,'Hamburger Hummersuppe',6.4599999999999999644);
INSERT INTO food VALUES(5,'Knackwurst',9.9900000000000002131);
INSERT INTO food VALUES(5,'Krabbentoast',6.9199999999999999289);
INSERT INTO food VALUES(5,'Franzbrötchen',12.740000000000000213);
INSERT INTO food VALUES(6,'Bacalhau',5.4900000000000002131);
INSERT INTO food VALUES(6,'Caldeirada',7.6299999999999998934);
INSERT INTO food VALUES(6,'Alcatra',18.660000000000000142);
INSERT INTO food VALUES(7,'Yorkshire Pudding',3.4900000000000002131);
INSERT INTO food VALUES(7,'Bangers and Mash',6.6299999999999998934);
INSERT INTO food VALUES(7,'Sticky Toffee Pudding',5.6600000000000001421);
INSERT INTO food VALUES(8,'Bocata de calamares',6.9599999999999999644);
INSERT INTO food VALUES(8,'Oreja a la plancha',11.849999999999999644);
INSERT INTO food VALUES(8,'Caracoles a la madrileña',6.9400000000000003907);
INSERT INTO food VALUES(9,'Caramels',4.7599999999999997868);
INSERT INTO food VALUES(9,'Bordier Butter',5.6500000000000003552);
INSERT INTO food VALUES(9,'Baguette',4.9900000000000002131);
INSERT INTO food VALUES(9,'Pain au Chocolat',4.6900000000000003907);
INSERT INTO food VALUES(10,'Beef steak tartare',18.760000000000001563);
INSERT INTO food VALUES(10,'Kulajda',6.8899999999999996802);
INSERT INTO food VALUES(10,'Svickova',5.9800000000000004263);
INSERT INTO food VALUES(10,'Roast duck',14.689999999999999502);
INSERT INTO food VALUES(11,'Spaghetti alla Carbonara',6.7300000000000004263);
INSERT INTO food VALUES(11,'Bruschetta',4.8499999999999996447);
INSERT INTO food VALUES(11,'Scaloppine',12.990000000000000212);
INSERT INTO food VALUES(11,'Rigatoni con la Pajata',8.7899999999999991473);
INSERT INTO food VALUES(11,'Carciofi alla giudia',15.990000000000000213);
CREATE TABLE accounts(username TEXT, password TEXT, level TEXT);
INSERT INTO accounts VALUES('admin','password','ADMIN');
DELETE FROM sqlite_sequence;
INSERT INTO sqlite_sequence VALUES('cities',11);
COMMIT;
