//
// Created by MarcelBenders on 04.09.2017.
//

#ifndef SOM_SET_H
#define SOM_SET_H

#include "setinfo.h"
namespace com_b_velop{
  struct Set : public SetInfo
  {
    /**
     * 2D Datenstruktur [zeile, werte]
     * Hier liegen die skalierten Trainingsdaten
     */
    double **values;

    /**
     * Die Anzahl der Zeilen in values
     */
    size_t rows;

    /**
     * Die Anzahl der Spalten in values
     */
    size_t cols;

    /**
     * Standardkonstruktor
     */
    Set(){};

    /**
     * Konstruktor, die ankommenden Werte werden direk in Values kopiert
     * @param in_values 2D vector<double> [row, col] mit Daten
     */
    Set(const vector<vector<double>> &in_values);

    /**
     * Destruktor
     */
    ~Set();

    /**
     * Kopiert die Daten in_values in values
     * @param in_values 2D vector<double> [row, col] mit Daten
     * @return Gibt das Set zurück
     */
    Set *SetSet(const vector<vector<double>> &in_values);

    /**
     * Teilt das Set in in_percent und 100  ´- in_percent auf. Dabei werden zufällig Daten entnommen. Das Original-Set
     * enthält diese Daten nicht mehr.
     * @param in_percent Angabe in Prozent, wieviel vom Set apgesplittet werden sollen.
     * @return Ein neues Set mit in_percent Prozent zufällig gewählten Daten vom Original Set.
     */
    Set *SplitValues(const unsigned short &in_percent);

    /**
     * Speicher für die Daten wird allokiert. Dieser wird mit 0 initialisiert.
     * @param in_rows Die Anzahl der Zeilen
     * @param in_cols Die Anzahl der Spalten
     * @return Das Set
     */
    Set *InitValues(const size_t &in_rows, const size_t &in_cols);

    /**
     * Git den allokierten Speicher wieder frei
     * @return Das Set-Objekt
     */
    Set *DeallocValues();

    /**
     * Deserialisiert das Set.
     * @param in_source Der Pfad zum deserialisierten Set
     * @return Das geladene Set-Objekt
     */
    static Set *OpenSet(const char *in_source);

    /**
     * Serialisiert das Set-Objekt
     * @param in_destination Der Zielname der Datei
     * @return Das Set-Objekt
     */
    Set *SaveSet(const char *in_destination);
  };
} // namespace com_b_velop
#endif //SOM_SET_H
