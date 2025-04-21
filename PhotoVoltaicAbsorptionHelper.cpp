#include<iostream>
#include<iomanip>
#include<string>
#include<cmath>
#include<fstream>

// Author: Ethan Dicke
// Date: 4/20/2025
// Purpose: make an abosrption file for Adept 2.1 on NanoHub

using namespace std;

double calcAbsorbance(double wavelength, double bandGapEnergy, double n) {
	const double A = pow(10,5); // cm^ -1 eV ^ -1/2
	const double h = 4.1357 * pow(10, -15); // eV * s
	const double c = 3 * pow(10, 8) * 100 ; // cm/s
	double wavelengthCm = wavelength * pow(10, -7);
	double Energy = (h * c) / wavelengthCm;
	if ((Energy - bandGapEnergy < 0) && n < 1){
		return 0;
	}
	else {
		return A * pow((Energy - bandGapEnergy), n);;
	}
}

int main(){
	ofstream outFS;
	string material = "Si";
	const int numItems = 500;
	double bandGapEnergy = 1.12;
	double wavelength;
	const double deltaWavelength = 2.0;
	double n = 2;
	string input;
	cout << "Enter the name of your element: ";
	cin >> material;
	cout << "What is the Band Gap Energy of your material? (in eV) : ";
	cin >> bandGapEnergy;
	cout << "What is the Electron Transition type" << endl;
	cout << "type \"da\" for allowed direct" << endl;
	cout << "type \"df\" for forbidden direct" << endl;
	cout << "type \"ia\" for allowed indirect" << endl;
	cout << "type \"if\" for forbidden indirect" << endl;
	cout << ": ";
	cin >> input;
	if (input == "da") {
		n = 0.5 ;
	}
	else if (input == "df") {
		n = 1.5;
	}
	else if (input == "ia") {
		n = 2;
	}
	else if (input == "if") {
		n = 3;
	}
	else {
		cout << "Incorrect type specified closing down" << endl;
		return 0;
	}
	string fileName = material + "AbsorptionFile.txt";
	outFS.open(fileName);
	if (!outFS.is_open()) {
		cout << "file creating Error occured" << endl;
		return 0;
	}
	outFS << material << " Absorption Coefficient File" << endl;
	outFS << numItems << endl;
	outFS << fixed << scientific << setprecision(3);
	for (wavelength = 200; wavelength < 1200; wavelength += deltaWavelength) {
		outFS << wavelength * pow(10, -3) << "  " << calcAbsorbance(wavelength, bandGapEnergy, n);
		if (wavelength < 1198) { outFS << endl; }
	}
	outFS.close();
	cout << "File has been successfully created as " << fileName << " " << endl;
	return 1;
}