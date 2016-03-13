#!/bin/bash

VERSION_OLD=1.0.4
VERSION_NEW=1.0.5

for FILE in de.morknet.sct.qt.*/pom.xml
do
	echo $FILE
	sed -e "0,/${VERSION_OLD}/s//${VERSION_NEW}-SNAPSHOT/" -i ${FILE}
done

for FILE in de.morknet.sct.qt.*/feature.xml de.morknet.sct.qt.*/META-INF/MANIFEST.MF
do
	echo $FILE
	sed -e "s/${VERSION_OLD}/${VERSION_NEW}.qualifier/g" -i ${FILE}
done

for FILE in de.morknet.sct.qt.updatesite/*.xml
do
	echo $FILE
	sed -e "s/${VERSION_OLD}.qualifier/${VERSION_NEW}.qualifier/g" -i ${FILE}
done

sed -e "s/%RELEASE%/false/g" -e "s/%SNAPSHOT%/true/g" p2.template >de.morknet.sct.qt.feature/p2.inf
