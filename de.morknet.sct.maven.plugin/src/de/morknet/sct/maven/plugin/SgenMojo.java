package de.morknet.sct.maven.plugin;

import java.io.File;

import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugins.annotations.LifecyclePhase;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.Parameter;

@Mojo(name = "sct", defaultPhase = LifecyclePhase.TEST)
public class SgenMojo extends AbstractMojo
{

	@Parameter(name = "sgen", required = true)
	private File sgen;

	/**
	 * Says "Hi" to the user.
	 *
	 */
	public void execute() throws MojoExecutionException
	{
		getLog().info("Hello, world.");
		getLog().info(sgen.getAbsolutePath());
	}
}
