#ifndef _SEQUENCER_H
#define _SEQUENCER_H

class SequencerClass
{
public:
	static void onShow();
	static void updateStatus();
	static void handle();
	static void midiUpdate();
};

extern SequencerClass Sequencer;

#endif
