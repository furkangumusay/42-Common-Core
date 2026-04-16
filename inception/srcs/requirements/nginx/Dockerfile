FROM debian:bookworm

RUN apt-get update && apt-get install -y \
    nginx \
    openssl \
    && rm -rf /var/lib/apt/lists/*

# Create SSL certificate directory
RUN mkdir -p /etc/nginx/ssl

# Generate self-signed SSL certificate
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/nginx.key \
    -out /etc/nginx/ssl/nginx.crt \
    -subj "/C=TR/ST=Istanbul/L=Istanbul/O=42/OU=42/CN=fgumusay.42.fr"

# Copy nginx configuration
COPY conf/nginx.conf /etc/nginx/nginx.conf

# Expose port 443
EXPOSE 443

# Run nginx in foreground
CMD ["nginx", "-g", "daemon off;"]
