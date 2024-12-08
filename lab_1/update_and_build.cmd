@echo off

echo Обновление исходников...
git pull origin main || exit /b 1

echo Сборка проекта...
make || exit /b 1

echo Сборка завершена!
