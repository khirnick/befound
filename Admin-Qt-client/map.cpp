#include "map.h"

#include <marble/GeoDataTreeModel.h>
#include <marble/MarbleModel.h>
#include <marble/GeoDataPlacemark.h>

void Map::setMapCenter(double lon, double lat)
{
    this->centerOn(Marble::GeoDataCoordinates(lon, lat, 0, Marble::GeoDataCoordinates::Degree));
    this->setZoom(Globals::baseZoom);
}

Map::Map(QWidget *obj) :
    MarbleWidget(obj), m_track(NULL)
{
    this->setProjection(Marble::Mercator);
    this->setMapThemeId("earth/openstreetmap/openstreetmap.dgml");
    setMapCenter(Globals::baseLongitude, Globals::baseLatitude);

    m_geoDataDocument = new Marble::GeoDataDocument;
    // Add the document to MarbleWidget's tree model
    this->model()->treeModel()->addDocument(m_geoDataDocument);
}

void Map::customPaint(GeoPainter *painter)
{
    // Рисую трек
    if (m_track) {
        painter->setPen( Qt::blue );
        painter->drawPolyline( *m_track );
    }
}

void Map::drawUsersCoords(QList<Globals::User> &users)
{
    this->model()->treeModel()->removeDocument(m_geoDataDocument);
    m_geoDataDocument->clear();
    for (QList<Globals::User>::iterator i = users.begin(); i != users.end(); ++i) {
        Marble::GeoDataPlacemark *user = new Marble::GeoDataPlacemark(i->last_name + " " + i->first_name);
        user->setId(QString() + i->id);
        user->setCoordinate( i->longitude, i->latitude, 0.0, Marble::GeoDataCoordinates::Degree );
        m_geoDataDocument->append(user);
    }
    this->model()->treeModel()->addDocument(m_geoDataDocument);
}

void Map::setTrack(QList<Globals::Coords> *track)
{
    if (track) {
        if (!m_track) {
            m_track = new GeoDataLineString( RespectLatitudeCircle | Tessellate );
        }
        for (QList<Globals::Coords>::iterator i = track->begin(); i != track->end(); ++i) {
            m_track->append(GeoDataCoordinates(i->longitude, i->latitude, 0.0, Marble::GeoDataCoordinates::Degree));
        }
    } else {
        delete m_track;
        m_track = NULL;
    }
}
