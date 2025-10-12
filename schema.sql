CREATE TABLE players (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(24),
    password VARCHAR(100),
    money INT DEFAULT 5000,
    races_won INT DEFAULT 0,
    races_lost INT DEFAULT 0,
    total_races INT DEFAULT 0
);

CREATE TABLE races (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(64),
    checkpoints TEXT,
    record_time INT,
    record_holder VARCHAR(24)
);

CREATE TABLE vehicles (
    id INT AUTO_INCREMENT PRIMARY KEY,
    owner_id INT,
    model INT,
    color1 INT,
    color2 INT,
    pos_x FLOAT,
    pos_y FLOAT,
    pos_z FLOAT,
    pos_a FLOAT
);