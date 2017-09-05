//
// Created by MarcelBenders on 04.09.2017.
//
#ifndef SOM_SETINFO_H
#define SOM_SETINFO_H
#include "feature.h"
#include <vector>
#include <string>

namespace com_b_velop{
  struct SetInfo
  {
    std::vector<Feature> features;

    /**
     * Anzahl der Features im Trainingssatz
     */
    size_t features_size;

    /**
     * Serialisiert SetInfo
     * @param stream Ein Datenstream
     * @return Ein SetInfo-Objekt wird zurückgegeben
     */
    SetInfo SaveSetInfo(std::ofstream &stream);

    /**
     * Deserialisiert SetInfo
     * @param stream Der Dateistream
     * @return Das geladene SetInfo-Objekt
     */
    static SetInfo OpenSetInfo(std::ifstream &stream);

    /**
     * Gibt Informationen über das SetInfo-Objekt in der Standardausgabe aus
     */
    void Print() const;

    /**
     * Gibt Informationen über das SetInfo-Objekt zurück
     * @return Informationen als String
     */
    std::string ToString() const;
  };
} // namespace com_b_velop
#endif //SOM_SETINFO_H
