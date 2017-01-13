#pragma once
#include <SFML\Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <thread>

#define WINDOWWIDTH 1024
#define WINDOWHEIGHT 768
#define LINE ((WINDOWWIDTH)/(12))
#define DEBUG 1

/*
	TO DO LIST:
 
		PRIORYTETY
 #   Mechanizm Fal  ( Fale Specjalne,Fale Zwyk³e oraz Czasówki gdzie modyfikujemy randomEnemy + ograniczona iloœæ przeciwników)
 #  refaktoryzacja i optymalizacja za pomoc¹ dynamicznej alokacji oraz u¿ycie w¹tków (std::Thread albo w¹tki WinApi )

 #   Dodawnie Tekstur oraz Spriteów 
 #   Dodanie Powerupów (Pomys³ Jêdrzeja) oraz wiêkszej iloœci broni ( karabin maszynowy,Bazooka, miotacz ognia ? 
 #	 Sklep ! (Powerupy, bronie, amunicja, wie¿yczki(?) )

 */