@echo off

echo Обновление исходников...
git pull origin main || exit /b 1

echo Создаем директорию для сборки...
mkdir build
cd build

echo Конфигурация проекта...
cmake -G "MinGW Makefiles" ..

echo Собираем проект...
cmake --build .

echo Сборка завершена!
