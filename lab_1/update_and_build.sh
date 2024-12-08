#!/bin/bash

echo Обновление исходников...
git pull origin main || exit 1

echo Создаем директорию для сборки...
mkdir build
cd build

echo Конфигурация проекта...
cmake ..

echo Собираем проект...
cmake --build .

echo Сборка завершена!
