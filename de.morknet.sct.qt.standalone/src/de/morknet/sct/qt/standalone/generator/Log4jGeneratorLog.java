/*
 * $Id$
 * $Author$
 */

package de.morknet.sct.qt.standalone.generator;

import java.util.List;

import org.apache.log4j.Logger;

import com.google.common.collect.Lists;

public class Log4jGeneratorLog implements IGeneratorLog {
	private static final Logger          LOG = Logger.getLogger(Log4jGeneratorLog.class);
	private static final List<String>    lines = Lists.newArrayList();
	private static final List<Throwable> throwables = Lists.newArrayList();

	@Override
	public void writeToConsole(String line) {
		lines.add(line);
		LOG.info(line);
	}

	@Override
	public void writeToConsole(Throwable t) {
		throwables.add(t);
		LOG.error(t.getMessage(), t);
	}

	@Override
	public void close() throws Throwable {

	}
}