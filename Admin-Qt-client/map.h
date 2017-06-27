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

private:
    inline void setMapCenter(double lon, double lat);

public:
    Map(QWidget *obj = NULL);

    virtual void customPaint(GeoPainter* painter);
    void drawUsersCoords(QList<Globals::User> &users);
    void setTrack(QList<Globals::Coords> *track = NULL);
};

#endif // MAP_H
