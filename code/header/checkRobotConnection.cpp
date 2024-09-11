
#include <QProcess>
#include "header/checkRobotConnection.h"

bool checkRobotConnection()
{
    QProcess process;
    process.start("rostopic list");
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    QStringList topics = output.split("\n");

    return topics.contains("/joint_states");
}