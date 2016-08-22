#!/bin/bash

VERSION=1.0.8

for FILE in de.morknet.sct.qt.*/pom.xml
do
	echo $FILE
	sed -e "0,/${VERSION}-SNAPSHOT/s//${VERSION}/" -i ${FILE}
done

for FILE in de.morknet.sct.qt.*/feature.xml de.morknet.sct.qt.*/META-INF/MANIFEST.MF
do
	echo $FILE
	sed -e "s/${VERSION}.qualifier/${VERSION}/g" -i ${FILE}
done

sed -e "s/%RELEASE%/true/g" -e "s/%SNAPSHOT%/false/g" p2.template >de.morknet.sct.qt.feature/p2.inf
