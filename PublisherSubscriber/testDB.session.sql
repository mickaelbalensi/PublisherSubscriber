CREATE TABLE Coordinate (
    Id INTEGER  PRIMARY KEY AUTOINCREMENT,
    Longitude REAL NOT NULL,
    Latitude REAL NOT NULL
);

CREATE TABLE Colors (
    [Name] TEXT PRIMARY KEY
);

INSERT INTO Colors ([Name]) VALUES ('red'), ('blue'), ('green');

CREATE TABLE ShapesType (
    [Name] TEXT PRIMARY KEY
);

INSERT INTO ShapesType ([Name]) VALUES ('circle'), ('rectangle');

CREATE TABLE Shapes (
    Id INTEGER PRIMARY KEY AUTOINCREMENT,
    [Type] TEXT NOT NULL,
    [Version] INTEGER NOT NULL
);

CREATE TABLE Circles (
    ShapeID INTEGER PRIMARY KEY,
    AdditionalAttributes TEXT,
    FOREIGN KEY (ShapeID) REFERENCES Shapes(Id)
);

CREATE TABLE Rectangles (
    ShapeID INTEGER PRIMARY KEY,
    AdditionalAttributes TEXT,
    FOREIGN KEY (ShapeID) REFERENCES Shapes(Id)
);
