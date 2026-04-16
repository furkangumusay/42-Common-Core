#!/bin/bash

set -e

SSL_DIR="./nginx/ssl"
BACKEND_CERTS_DIR="./ft_transcendence-backend/backend/certs"

echo "Generating SSL certificates..."

mkdir -p "$SSL_DIR"
mkdir -p "$BACKEND_CERTS_DIR"

openssl req -x509 \
  -newkey rsa:4096 \
  -keyout "$SSL_DIR/key.pem" \
  -out "$SSL_DIR/cert.pem" \
  -days 365 \
  -nodes \
  -subj "/C=TR/ST=Istanbul/L=Istanbul/O=ft_transcendence/OU=DevOps/CN=localhost" \
  -addext "subjectAltName=DNS:localhost,IP:127.0.0.1"

echo "Nginx SSL certificates created: $SSL_DIR/"

cp "$SSL_DIR/key.pem" "$BACKEND_CERTS_DIR/key.pem"
cp "$SSL_DIR/cert.pem" "$BACKEND_CERTS_DIR/cert.pem"

echo "Backend certificates copied: $BACKEND_CERTS_DIR/"

chmod 600 "$SSL_DIR/key.pem"
chmod 644 "$SSL_DIR/cert.pem"
chmod 600 "$BACKEND_CERTS_DIR/key.pem"
chmod 644 "$BACKEND_CERTS_DIR/cert.pem"

echo ""
echo "SSL certificates are ready!"
echo "   Nginx:   $SSL_DIR/cert.pem + key.pem"
echo "   Backend: $BACKEND_CERTS_DIR/cert.pem + key.pem"
echo ""
echo "Note: This self-signed certificate is for development/testing only."
echo "    You may get browser security warnings. To bypass SSL errors:"
echo "    Chrome: chrome://flags -> 'Allow invalid certificates for resources loaded from localhost'"
