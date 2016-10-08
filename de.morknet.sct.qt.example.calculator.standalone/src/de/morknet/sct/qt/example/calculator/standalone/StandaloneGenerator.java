package de.morknet.sct.qt.example.calculator.standalone;

import de.morknet.sct.qt.standalone.StatemachineGenerator;

public class StandaloneGenerator
{
	public static void main(String[] args)
	{
		final StatemachineGenerator generator = new StatemachineGenerator();
		final String[] models =
		{
				"../de.morknet.sct.qt.example.calculator/model/calculator.sct",
				"../de.morknet.sct.qt.example.calculator/model/qt.sgen",
				"../de.morknet.sct.qt.example.calculator/model/cpp.sgen"
		};

		generator.doIt(models);
	}
}
