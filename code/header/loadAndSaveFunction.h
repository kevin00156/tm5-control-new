#ifndef LOADANDSAVEFUNCTION_H
#define LOADANDSAVEFUNCTION_H

void saveWidgetState(QWidget *widget, QSettings &settings);
void loadWidgetState(QWidget *widget, QSettings &settings);
bool hasRelevantChildren(QWidget *widget);

#endif // LOADANDSAVEFUNCTION_H