import QtQuick 2.6
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3

Item {
    id: dbLoadView
    anchors.fill: parent

    GroupBox {
        anchors.fill: parent

        GridLayout {
            id: grid
            columns: 4
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right

            Label { text: "Database: "}
            TextField { id: path; Layout.fillWidth: true; readOnly: true; }
            Button {
                text: "Load"
                onClicked: App.LoadDatabase(path.text)
            }
            Button {
                text: "Browse"
                onClicked: fileSelect.open()
            }
        }
    }
    
    FileDialog {
        id: fileSelect
        title: "Please choose a .json database"
        selectMultiple: false
        onAccepted: {
            path.text = fileSelect.fileUrls[0]
        }
        visible: false
    }
}