#!/bin/bash

rsync -av --delete de.morknet.sct.qt.updatesite/target/repository/\
	stmork,sctqtgen@web.sourceforge.net:/home/pfs/project/sctqtgen/repositories/snapshot/
rsync -av --delete de.morknet.sct.qt.updatesite/target/repository/\
	stmork,sctqtgen@web.sourceforge.net:/home/project-web/sctqtgen/htdocs/updates/snapshot/
