import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

  Rectangle {


    Plugin{
    id: mapPlugin
    name : "osm"

    }
    Map{
        id: mapView
        anchors.fill:parent
        plugin:mapPlugin
        center :QtPositioning.coordinate(36.81897 , 10.16579);
        zoomLevel : 10
    }

}
