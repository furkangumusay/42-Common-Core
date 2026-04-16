#!/bin/bash

# Check if database needs initialization
if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "Initializing MariaDB data directory..."
    mysql_install_db --user=mysql --datadir=/var/lib/mysql
    INIT_DB=true
else
    echo "MariaDB data directory already exists."
    INIT_DB=false
fi

# Start MariaDB temporarily in background
echo "Starting MariaDB..."
mysqld --user=mysql --datadir=/var/lib/mysql &
MYSQL_PID=$!

# Wait for MariaDB to be ready
echo "Waiting for MariaDB to be ready..."
sleep 5
until mysqladmin ping >/dev/null 2>&1; do
    echo "Still waiting for MariaDB..."
    sleep 2
done
echo "MariaDB is ready!"

# Check if wordpress database exists
if ! mysql -u root -e "USE ${MYSQL_DATABASE}" 2>/dev/null; then
    echo "Creating database and users..."
    mysql -u root <<EOF
-- Create database
CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;

-- Create user and grant privileges from any host
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'localhost' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'localhost';

-- Allow root from any host
CREATE USER IF NOT EXISTS 'root'@'%' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' WITH GRANT OPTION;

-- Flush privileges
FLUSH PRIVILEGES;
EOF
    echo "Database and users created successfully!"
else
    echo "Database ${MYSQL_DATABASE} already exists."
fi

# Stop the background MariaDB
echo "Restarting MariaDB in foreground mode..."
kill $MYSQL_PID
wait $MYSQL_PID 2>/dev/null
sleep 2

# Start MariaDB in foreground
exec mysqld --user=mysql --datadir=/var/lib/mysql
