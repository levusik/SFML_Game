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
#define DEBUG 0

/*
	TO DO LIST:
 
		PRIORYTETY
 #   Mechanizm Fal  ( Fale Specjalne,Fale Zwyk�e oraz Czas�wki gdzie modyfikujemy randomEnemy + ograniczona ilo�� przeciwnik�w)
 #  refaktoryzacja i optymalizacja za pomoc� dynamicznej alokacji oraz u�ycie w�tk�w (std::Thread albo w�tki WinApi )

 #   Dodawnie Tekstur oraz Sprite�w 
 #   Dodanie Powerup�w (Pomys� J�drzeja) oraz wi�kszej ilo�ci broni ( karabin maszynowy,Bazooka, miotacz ognia ? 
 #	 Sklep ! (Powerupy, bronie, amunicja, wie�yczki(?) )

 */