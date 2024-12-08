#!/bin/bash

echo "Обновление исходников..."
git pull origin main || exit 1

echo "Сборка проекта..."
make || exit 1

echo "Сборка завершена!"
