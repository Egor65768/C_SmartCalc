#!/bin/bash

IMAGE_NAME="my_image_for_test"

echo "Установка калькулятора в Docker"

echo "Сборка Docker образа..."
sudo docker build -t $IMAGE_NAME .
echo "Сборка Docker завершена"

echo "Запуск контейнера..."
sudo xhost +local:docker
sudo docker run -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix --rm $IMAGE_NAME
