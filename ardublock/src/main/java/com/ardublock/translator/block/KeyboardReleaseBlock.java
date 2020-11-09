package com.ardublock.translator.block;

import com.ardublock.translator.Translator;
import com.ardublock.translator.block.exception.SocketNullException;
import com.ardublock.translator.block.exception.SubroutineNotDeclaredException;

public class KeyboardReleaseBlock extends TranslatorBlock
{
	public KeyboardReleaseBlock(Long blockId, Translator translator, String codePrefix, String codeSuffix, String label)
	{
		super(blockId, translator, codePrefix, codeSuffix, label);
	}

	@Override
	public String toCode() throws SocketNullException, SubroutineNotDeclaredException
	{
		/**
		 * DO NOT add tab in code any more, we'll use arduino to format code, or the code will duplicated. 
		 */
		translator.addHeaderFile("Keyboard.h");
		translator.addSetupCommand("Keyboard.begin();");

		TranslatorBlock translatorBlock = this.getRequiredTranslatorBlockAtSocket(0, "Keyboard.release(", ");");

		return translatorBlock.toCode();
	}
}
