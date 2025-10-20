-- Players table
CREATE TABLE IF NOT EXISTS `players` (
  `id` INT AUTO_INCREMENT PRIMARY KEY,
  `name` VARCHAR(24) NOT NULL UNIQUE,
  `password` VARCHAR(255) NOT NULL,
  `money` INT DEFAULT 5000,
  `bank` INT DEFAULT 0,
  `level` INT DEFAULT 1,
  `rep` INT DEFAULT 0,
  `exp` INT DEFAULT 0,
  `total_races` INT DEFAULT 0,
  `races_won` INT DEFAULT 0,
  `races_lost` INT DEFAULT 0,
  `total_distance` FLOAT DEFAULT 0.0,
  `last_login` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  `created_at` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  `playtime` INT DEFAULT 0,
  INDEX `idx_name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Invidual player vehicles
CREATE TABLE IF NOT EXISTS `player_vehicles` (
  `id` INT AUTO_INCREMENT PRIMARY KEY,
  `player_id` INT NOT NULL,
  `model_id` INT NOT NULL,
  `color1` INT DEFAULT 0,
  `color2` INT DEFAULT 0,
  `paintjob` INT DEFAULT -1,
  `pos_x` FLOAT DEFAULT 0.0,
  `pos_y` FLOAT DEFAULT 0.0,
  `pos_z` FLOAT DEFAULT 0.0,
  `pos_a` FLOAT DEFAULT 0.0,
  `health` FLOAT DEFAULT 1000.0,
  `fuel` FLOAT DEFAULT 100.0,
  `plate` VARCHAR(32) DEFAULT NULL,
  `purchased_at` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  FOREIGN KEY (`player_id`) REFERENCES `players`(`id`) ON DELETE CASCADE,
  INDEX `idx_player_id` (`player_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Vehicle modifications
CREATE TABLE IF NOT EXISTS `vehicle_mods` (
  `id` INT AUTO_INCREMENT PRIMARY KEY,
  `vehicle_id` INT NOT NULL,
  `mod_slot` INT NOT NULL,
  `mod_type` INT NOT NULL,
  FOREIGN KEY (`vehicle_id`) REFERENCES `player_vehicles`(`id`) ON DELETE CASCADE,
  UNIQUE KEY `unique_mod` (`vehicle_id`, `mod_slot`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Race records/leaderboards
CREATE TABLE IF NOT EXISTS `race_records` (
  `id` INT AUTO_INCREMENT PRIMARY KEY,
  `race_id` INT NOT NULL,
  `player_id` INT NOT NULL,
  `race_type` ENUM('sprint', 'circuit', 'drift', 'drag', 'offroad', 'motorcycle') NOT NULL,
  `best_time` INT NOT NULL COMMENT 'Time in milliseconds',
  `best_score` INT DEFAULT 0 COMMENT 'For drift races',
  `vehicle_model` INT NOT NULL,
  `completed_at` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  FOREIGN KEY (`player_id`) REFERENCES `players`(`id`) ON DELETE CASCADE,
  INDEX `idx_race_id` (`race_id`),
  INDEX `idx_best_time` (`race_id`, `best_time`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Race checkpoints/tracks
CREATE TABLE IF NOT EXISTS `races` (
  `id` INT AUTO_INCREMENT PRIMARY KEY,
  `name` VARCHAR(64) NOT NULL,
  `race_type` ENUM('sprint', 'circuit', 'drift', 'drag', 'offroad', 'motorcycle') NOT NULL,
  `laps` INT DEFAULT 1,
  `reward_money` INT DEFAULT 1000,
  `reward_rep` INT DEFAULT 100,
  `min_level` INT DEFAULT 1,
  `created_by` INT DEFAULT NULL,
  `created_at` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  INDEX `idx_race_type` (`race_type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Race checkpoints
CREATE TABLE IF NOT EXISTS `race_checkpoints` (
  `id` INT AUTO_INCREMENT PRIMARY KEY,
  `race_id` INT NOT NULL,
  `checkpoint_order` INT NOT NULL,
  `pos_x` FLOAT NOT NULL,
  `pos_y` FLOAT NOT NULL,
  `pos_z` FLOAT NOT NULL,
  `size` FLOAT DEFAULT 10.0,
  FOREIGN KEY (`race_id`) REFERENCES `races`(`id`) ON DELETE CASCADE,
  INDEX `idx_race_id` (`race_id`, `checkpoint_order`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Player statistics (daily/nightly tracking like NFS Heat)
CREATE TABLE IF NOT EXISTS `player_stats` (
  `id` INT AUTO_INCREMENT PRIMARY KEY,
  `player_id` INT NOT NULL,
  `stat_date` DATE NOT NULL,
  `day_money_earned` INT DEFAULT 0,
  `night_rep_earned` INT DEFAULT 0,
  `races_completed` INT DEFAULT 0,
  `distance_driven` FLOAT DEFAULT 0.0,
  -- TODO: add more stats
  FOREIGN KEY (`player_id`) REFERENCES `players`(`id`) ON DELETE CASCADE,
  UNIQUE KEY `unique_stat` (`player_id`, `stat_date`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Bans table
CREATE TABLE IF NOT EXISTS `bans` (
  `id` INT AUTO_INCREMENT PRIMARY KEY,
  `player_name` VARCHAR(24) NOT NULL,
  `ip_address` VARCHAR(16) DEFAULT NULL, -- hehe
  `reason` VARCHAR(128) NOT NULL,
  `banned_by` VARCHAR(24) NOT NULL,
  `banned_at` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  `expires_at` TIMESTAMP NULL DEFAULT NULL,
  INDEX `idx_player_name` (`player_name`),
  INDEX `idx_ip_address` (`ip_address`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
