import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0

ApplicationWindow {
    id: root
    width: 480
    height: 300
    visible: true
    title: "Food Management"

    TabView {
        id: tabs
        anchors.fill: parent
        
        Tab {
            title: "Welcome"
            active: true
            Label {
                id: sup
                text: "Sup"
            }
        }
        
        Tab {
            title: "DB Load"
            DbLoadView { anchors.fill: parent}
        }
    }
}