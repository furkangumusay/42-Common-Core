.PHONY: help setup ssl start stop restart logs clean status build remove

setup: ssl
	@echo "Preparing environment file..."
	@if [ ! -f .env ]; then \
		cp .env.example .env; \
		echo ".env file created. Do not forget to fill in the values!"; \
	else \
		echo ".env file already exists, skipping."; \
	fi
	@echo "Building Docker images..."
	docker compose build
	@echo ""
	@echo "Setup complete! To start: make start"

ssl:
	@chmod +x scripts/generate-ssl.sh
	@./scripts/generate-ssl.sh

start:
	@echo "Starting services..."
	docker compose up -d
	@echo ""
	@echo "Services are running! Check status: make status"

stop:
	@echo "Stopping services..."
	docker compose down

restart:
	@echo "Restarting services..."
	docker compose restart

build:
	@echo "Rebuilding Docker images..."
	docker compose build --no-cache

status:
	@echo "Service Status:"
	@echo "------------------------------------------------------"
	docker compose ps
	@echo ""
	@echo "Health checks:"
	@docker compose ps --format "table {{.Name}}\t{{.Status}}" 2>/dev/null || true

logs:
	docker compose logs -f --tail=100

logs-%:
	docker compose logs -f --tail=100 $*

elk-setup:
	@echo "Setting up ELK ILM policy..."
	@echo "Waiting for Elasticsearch to be ready..."
	@sleep 10
	@chmod +x scripts/setup-elk-ilm.sh
	@./scripts/setup-elk-ilm.sh

remove:
	@echo "Removing all containers..."
	@if [ -n "$$(docker ps -aq)" ]; then \
		docker rm -f $$(docker ps -aq); \
		echo "Containers removed."; \
	else \
		echo "No containers to remove."; \
	fi
	@docker compose down --remove-orphans 2>/dev/null || true

clean:
	@echo "Removing all containers and volumes..."
	@read -p "WARNING: All data will be deleted! Are you sure? [y/N] " confirm; \
	if [ "$$confirm" = "y" ] || [ "$$confirm" = "Y" ]; then \
		docker compose down -v --remove-orphans; \
		echo "Cleanup complete."; \
	else \
		echo "Cancelled."; \
	fi

clean-images:
	@echo "Removing unused Docker images..."
	docker image prune -f

health:
	@echo "Service health checks:"
	@echo "---------------------------------------------"
	@echo -n "  Backend:       "; curl -sk http://localhost:3000/health 2>/dev/null | python3 -c "import sys,json; d=json.load(sys.stdin); print('UP' if d else 'DOWN')" 2>/dev/null || echo "UNREACHABLE"
	@echo -n "  Elasticsearch: "; curl -sk -u elastic:$${ELASTIC_PASSWORD:-changeme} http://localhost:9200/_cluster/health 2>/dev/null | python3 -c "import sys,json; d=json.load(sys.stdin); print(d.get('status','?').upper())" 2>/dev/null || echo "UNREACHABLE"
	@echo -n "  Kibana:        "; curl -sk http://localhost:5601/api/status 2>/dev/null | python3 -c "import sys,json; d=json.load(sys.stdin); print('UP')" 2>/dev/null || echo "UNREACHABLE"
	@echo -n "  Prometheus:    "; curl -sk http://localhost:9090/-/healthy 2>/dev/null | grep -q "Healthy" && echo "UP" || echo "UNREACHABLE"
	@echo -n "  Grafana:       "; curl -sk http://localhost:3001/api/health 2>/dev/null | python3 -c "import sys,json; d=json.load(sys.stdin); print(d.get('database','?'))" 2>/dev/null || echo "UNREACHABLE"
