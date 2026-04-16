#!/bin/bash

cd /var/www/html

# Wait for MariaDB to be ready
echo "Waiting for MariaDB to be ready..."
while ! mysqladmin ping -h mariadb -u ${MYSQL_USER} -p${MYSQL_PASSWORD} --silent; do
    echo "MariaDB is not ready yet. Waiting..."
    sleep 3
done
echo "MariaDB is ready!"

# Download WordPress if not present
if [ ! -f /var/www/html/wp-config.php ]; then
    echo "Downloading WordPress..."
    wp core download --allow-root
    
    echo "Creating wp-config.php..."
    wp config create \
        --dbname=${MYSQL_DATABASE} \
        --dbuser=${MYSQL_USER} \
        --dbpass=${MYSQL_PASSWORD} \
        --dbhost=mariadb:3306 \
        --allow-root
    
    echo "Installing WordPress..."
    wp core install \
        --url=https://${DOMAIN_NAME} \
        --title="${WP_TITLE}" \
        --admin_user=${WP_ADMIN_USER} \
        --admin_password=${WP_ADMIN_PASSWORD} \
        --admin_email=${WP_ADMIN_EMAIL} \
        --skip-email \
        --allow-root
    
    echo "Creating additional WordPress user..."
    wp user create ${WP_USER} ${WP_USER_EMAIL} \
        --user_pass=${WP_USER_PASSWORD} \
        --role=author \
        --allow-root
    
    # Set correct ownership
    chown -R www-data:www-data /var/www/html
    
    echo "WordPress installation complete!"
else
    echo "WordPress is already installed."
fi

# Start PHP-FPM in foreground
echo "Starting PHP-FPM..."
exec php-fpm8.2 -F
