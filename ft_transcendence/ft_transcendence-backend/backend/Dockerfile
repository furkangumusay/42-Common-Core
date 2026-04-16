FROM node:20-bookworm-slim AS base
WORKDIR /app

RUN apt-get update && apt-get install -y python3 make g++ && rm -rf /var/lib/apt/lists/*

COPY package*.json ./

FROM base AS development
RUN npm install
COPY . .
CMD ["npm", "run", "dev"]

FROM base AS builder
RUN npm install
COPY . .
RUN npm run build
RUN npm prune --production

FROM node:20-bookworm-slim AS production
WORKDIR /app

RUN apt-get update && apt-get install -y python3 make g++ wget gosu && rm -rf /var/lib/apt/lists/*

COPY --from=builder /app/package*.json ./
COPY --from=builder /app/dist ./dist

RUN npm ci --only=production

RUN mkdir -p uploads/avatars certs logs default-assets

COPY uploads/avatars/default-avatar.png default-assets/default-avatar.png
COPY uploads/avatars/default-avatar.png uploads/avatars/default-avatar.png

COPY docker-entrypoint.sh /app/docker-entrypoint.sh
RUN chmod +x /app/docker-entrypoint.sh

COPY database ./database

RUN chown -R node:node /app

EXPOSE 3000

HEALTHCHECK --interval=30s --timeout=5s --start-period=10s --retries=3 \
    CMD wget --no-verbose --tries=1 --spider --no-check-certificate https://localhost:3000/health || exit 1

ENTRYPOINT ["/app/docker-entrypoint.sh"]
CMD ["node", "dist/app.js"]
