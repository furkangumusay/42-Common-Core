# **************************************************************************** #
#                                                                              #
#    Inception Project Makefile                                                #
#                                                                              #
# **************************************************************************** #

NAME = inception

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

# Docker Compose command (use 'docker compose' for modern Docker)
DOCKER_COMPOSE = docker compose

# Docker Compose file path
COMPOSE_FILE = ./srcs/docker-compose.yml

# Data directories
DATA_DIR = /home/osboxes/data
WP_DATA = $(DATA_DIR)/wordpress
DB_DATA = $(DATA_DIR)/mariadb

all: setup build up

setup:
	@echo "$(YELLOW)Creating data directories...$(RESET)"
	@mkdir -p $(WP_DATA)
	@mkdir -p $(DB_DATA)
	@echo "$(GREEN)Data directories created.$(RESET)"

build:
	@echo "$(YELLOW)Building Docker images...$(RESET)"
	@$(DOCKER_COMPOSE) -f $(COMPOSE_FILE) build
	@echo "$(GREEN)Docker images built successfully.$(RESET)"

up:
	@echo "$(YELLOW)Starting containers...$(RESET)"
	@$(DOCKER_COMPOSE) -f $(COMPOSE_FILE) up -d
	@echo "$(GREEN)Containers started successfully.$(RESET)"

down:
	@echo "$(YELLOW)Stopping containers...$(RESET)"
	@$(DOCKER_COMPOSE) -f $(COMPOSE_FILE) down
	@echo "$(GREEN)Containers stopped.$(RESET)"

start:
	@echo "$(YELLOW)Starting existing containers...$(RESET)"
	@$(DOCKER_COMPOSE) -f $(COMPOSE_FILE) start
	@echo "$(GREEN)Containers started.$(RESET)"

stop:
	@echo "$(YELLOW)Stopping containers...$(RESET)"
	@$(DOCKER_COMPOSE) -f $(COMPOSE_FILE) stop
	@echo "$(GREEN)Containers stopped.$(RESET)"

restart: stop start

logs:
	@$(DOCKER_COMPOSE) -f $(COMPOSE_FILE) logs -f

ps:
	@$(DOCKER_COMPOSE) -f $(COMPOSE_FILE) ps

clean: down
	@echo "$(YELLOW)Removing Docker images...$(RESET)"
	@$(DOCKER_COMPOSE) -f $(COMPOSE_FILE) down --rmi all --volumes
	@echo "$(GREEN)Docker images removed.$(RESET)"

fclean: clean
	@echo "$(YELLOW)Removing data directories...$(RESET)"
	@sudo rm -rf $(DATA_DIR)
	@echo "$(YELLOW)Removing all Docker resources...$(RESET)"
	@docker system prune -af
	@echo "$(GREEN)Full cleanup complete.$(RESET)"

re: fclean all

status:
	@echo "$(YELLOW)=== Docker Containers ===$(RESET)"
	@docker ps -a
	@echo ""
	@echo "$(YELLOW)=== Docker Images ===$(RESET)"
	@docker images
	@echo ""
	@echo "$(YELLOW)=== Docker Volumes ===$(RESET)"
	@docker volume ls
	@echo ""
	@echo "$(YELLOW)=== Docker Networks ===$(RESET)"
	@docker network ls

.PHONY: all setup build up down start stop restart logs ps clean fclean re status
