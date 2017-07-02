#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QList>
#include <marble/MarbleWidget.h>
#include <marble/GeoPainter.h>
#include <marble/GeoDataLineString.h>
#include <marble/GeoDataDocument.h>
#include "globals.h"

using namespace Marble;

class Map : public MarbleWidget
{
    Marble::GeoDataDocument *m_geoDataDocument;
    Marble::GeoDataLineString *m_track;

public:
    Map(QWidget *obj = NULL);

    inline void setMapCenter(double lon, double lat);
    virtual void customPaint(GeoPainter* painter);
    void drawUsersCoords(QList<Globals::User> &users);
    void setTrack(QList<Globals::Coords> *track = NULL);
};

#endif // MAP_H
