////////////////////////////////////////////////////////////////////////////////////////
// PRESET
// V.0.0.1 2022-01-2
////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>
#include "spawner.hpp"

#define envn 6  // Number of envelopes
#define lfos 4  // Number of LFOs
#define nn	 12 // Number of notes

class preset
{
    public:
        const std::filesystem::path presets{"presets"};
        const string path_prefix = "presets/";
        vector<string> preset_list;
        std::string version = "0.4.6";
        std::fstream        ff;
        std::stringstream   ss;
        std::string name;
        size_t preset_count;
        
        float   volume  = 0.05;             // Master volume

        ///////////////////////////////////////////////////////////
        // Oscillators ////////////////////////////////////////////
        int     form_vco[oscn];             // Waveform
        ///////////////////////////////////////////////////////////
        int     amp_slider_type[oscn];      // Amplitude slider
        int     amp_mod_type[oscn];         // Mod type
        float   amp_mod_amount[oscn];       // Mod amount
        float   amp_centre[oscn];           // Amp value
        ///////////////////////////////////////////////////////////
        int     detune_slider_type[oscn];
        int     detune_mod_type[oscn];
        float   detune_mod_amount[oscn];
        float   detune_centre[oscn];
        ///////////////////////////////////////////////////////////
        int     pan_slider_type[oscn];
        int     pan_mod_type[oscn];
        float   pan_mod_amount[oscn];
        float   pan_centre[oscn];
        ///////////////////////////////////////////////////////////
        int     octave[oscn];
        ///////////////////////////////////////////////////////////
        int     phase_slider_type[oscn];
        int     phase_mod_type[oscn];
        float   phase_mod_amount[oscn];
        float   phase_centre[oscn];
        ///////////////////////////////////////////////////////////
        int     pwm_slider_type[oscn];
        int     pwm_mod_type[oscn];
        float   pwm_mod_amount[oscn];
        float   pwm_centre[oscn];
        ///////////////////////////////////////////////////////////
        int     filter_type[oscn];
        ///////////////////////////////////////////////////////////
        int     cuttoff_slider_type[oscn];
        int     cutoff_mod_type[oscn];
        float   cutoff_mod_amount[oscn];
        float   center_cutoff[oscn];
        float   cutoff[oscn];   /// ???????
        ///////////////////////////////////////////////////////////
        float   resonance[oscn];
        ///////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////
        // Envelopes //////////////////////////////////////////////
        envelope_adsr env[envn];
        vector<float> env_imprint[envn];
        int     env_slider_type[envn];
        int     env_form[envn];
        int     radio_env_amp       = 1;
        int     radio_env_mod       = 1;
        bool    env_freerun[3];
        float   env_scale[envn];

        ///////////////////////////////////////////////////////////
        // LFOs ///////////////////////////////////////////////////
        LFO     lfo[lfos];
        vector<float> lfo_imprint[lfos];

        int     lfo_form[lfos];
        int     lfo_mod_type[lfos];
        float   lfo_mod_amount[lfos];

        float   lfo_amp[lfos];
        float   lfo_morph[lfos];
        
        
        ///////////////////////////////////////////////////////////
        // Seuencer ///////////////////////////////////////////////
        bool    trigger_sequence    = true;
        vector<bool> note_set   = {1,0,0,0,0,0,0,0,0,0,0,0};
        vector<int>  oct_set    = {4,4,4,4,4,4,4,4,4,4,4,4};
        float   tempo           = 0.100f; 

        float   seed[2];
        float   step[2];
        uint    beat        = 0x80808080;
        int     rhythm[4]   = {128, 128, 128, 128};
        int     octaves     = 1;
        int     steps       = 32;
        int     direction[2];
        int     algorhithm[2];

        int     oct [nn]; // Octave values
        bool    note[nn]; // Note On & Off

        ///////////////////////////////////////////////////////////
        // Effects ////////////////////////////////////////////////

        int     delay_slider_type[oscn];
        float   ddtime_mod_amount[oscn];
        int     ddtime_mod_type[oscn];
        
        void save(const string&);
        void save();
        void load();
        void get_list();
        preset();
       ~preset();
};

void preset::get_list()
{
    int st = path_prefix.length()+1;
    preset_count = 0;
    for (auto const& entry : std::filesystem::directory_iterator{presets}) 
    {
        ss<<entry;
        name = ss.str().substr(st, ss.str().length() - st-1);
        preset_list.push_back(name);
        ss.str("");
        ss.clear();
        preset_count++;
    }
}

void preset::save()
{
    ff.open(path_prefix+name, std::ios_base::out);

    ff<<volume<<"\n";
    ///////////////////////////////////////////////////////////
    // Oscillators ////////////////////////////////////////////
    for(int i=0; i<oscn; i++) 
    {
        ff<<form_vco[i]<<"\n";
    ///////////////////////////////////////////////////////////
        ff<<amp_slider_type[i] <<"\n";
        ff<<amp_mod_type[i]<<"\n";
        ff<<amp_mod_amount[i]<<"\n";
        ff<<amp_centre[i]<<"\n";
    ///////////////////////////////////////////////////////////
        ff<<detune_slider_type[i]<<"\n";
        ff<<detune_mod_type[i]<<"\n";
        ff<<detune_mod_amount[i]<<"\n";
        ff<<detune_centre[i]<<"\n";
    ///////////////////////////////////////////////////////////
        ff<<pan_slider_type[i]<<"\n";
        ff<<pan_mod_type[i]<<"\n";
        ff<<pan_mod_amount[i]<<"\n";
        ff<<pan_centre[i]<<"\n";   
    ///////////////////////////////////////////////////////////
        ff<<octave[i]<<"\n";
    ///////////////////////////////////////////////////////////
        ff<<phase_slider_type[i]<<"\n";
        ff<<phase_mod_type[i]<<"\n";
        ff<<phase_mod_amount[i]<<"\n";
        ff<<phase_centre[i]<<"\n";
    ///////////////////////////////////////////////////////////
        ff<<pwm_slider_type[i]<<"\n";
        ff<<pwm_mod_type[i]<<"\n";
        ff<<pwm_mod_amount[i]<<"\n";
        ff<<pwm_centre[i]<<"\n";
    ///////////////////////////////////////////////////////////
        ff<<filter_type[i]<<"\n";
    ///////////////////////////////////////////////////////////
        ff<<cuttoff_slider_type[i]<<"\n";
        ff<<cutoff_mod_type[i]<<"\n";
        ff<<cutoff_mod_amount[i]<<"\n";
        ff<<center_cutoff[i]<<"\n";
        ff<<cutoff[i]<<"\n";
    ///////////////////////////////////////////////////////////
        ff<<resonance[i]<<"\n";
    ///////////////////////////////////////////////////////////
    }

    ///////////////////////////////////////////////////////////
    // Amp Envelopes //////////////////////////////////////////
	for(int i=0; i<envn; i++)
	{
		ff<<env[i].adsr.A.time<<"\n";
		ff<<env[i].adsr.D.time<<"\n";
		ff<<env[i].adsr.S.time<<"\n";
		ff<<env[i].adsr.R.time<<"\n";

		ff<<env[i].adsr.A.value<<"\n";
		ff<<env[i].adsr.D.value<<"\n";
		ff<<env[i].adsr.S.value<<"\n";
		ff<<env[i].adsr.R.value<<"\n";

		ff<<env_scale[i]<<"\n"; 

        ff<<env_slider_type[i]<<"\n";
        ff<<env_form[i]<<"\n";
        if(i<3) ff<<env_freerun[i]<<"\n";
	}

    ff<<radio_env_amp<<"\n";
    ff<<radio_env_mod<<"\n";
    
    ///////////////////////////////////////////////////////////
    // LFOs ///////////////////////////////////////////////////
	for(int i=0; i<lfos; i++)
	{
        ff<<lfo_form[i]<<"\n";
        ff<<lfo_mod_type[i]<<"\n";
        ff<<lfo_mod_amount[i]<<"\n";
        ff<<lfo[i].frequency<<"\n";
    }

    ///////////////////////////////////////////////////////////
    // Sequencer //////////////////////////////////////////////

    ff<<trigger_sequence<<"\n";
    ff<<tempo<<"\n";
    ff<<beat<<"\n";
    ff<<seed[0]<<"\n";
    ff<<seed[1]<<"\n";
    ff<<step[0]<<"\n";
    ff<<step[1]<<"\n";
    ff<<octaves<<"\n";
    ff<<steps<<"\n";

    ff<<direction[0]<<"\n";
    ff<<direction[1]<<"\n";

    ff<<algorhithm[0]<<"\n";
    ff<<algorhithm[1]<<"\n";

	for(int i=0; i<nn; i++)
	{
        ff<<note_set[i]<<"\n";
        ff<<oct_set[i]<<"\n";
		ff<<oct[i]<<"\n"; 
    	ff<<note[i]<<"\n";
	}

    ff.close();
}

void preset::load()
{
    ff.open(path_prefix+name, std::ios_base::in);

    ff>>volume;
    ///////////////////////////////////////////////////////////
    // Oscillators ////////////////////////////////////////////
    for(int i=0; i<oscn; i++) 
	{
        ff>>form_vco[i];
    ///////////////////////////////////////////////////////////
		ff>>amp_slider_type[i];
        ff>>amp_mod_type[i];
		ff>>amp_mod_amount[i];
        ff>>amp_centre[i];
    ///////////////////////////////////////////////////////////
        ff>>detune_slider_type[i];
        ff>>detune_mod_type[i];
        ff>>detune_mod_amount[i];
        ff>>detune_centre[i];
    ///////////////////////////////////////////////////////////
        ff>>pan_slider_type[i];
        ff>>pan_mod_type[i];
        ff>>pan_mod_amount[i];
        ff>>pan_centre[i];   
    ///////////////////////////////////////////////////////////
        ff>>octave[i];
    ///////////////////////////////////////////////////////////
        ff>>phase_slider_type[i];
        ff>>phase_mod_type[i];
        ff>>phase_mod_amount[i];
        ff>>phase_centre[i];
    ///////////////////////////////////////////////////////////
        ff>>pwm_slider_type[i];
        ff>>pwm_mod_type[i];
        ff>>pwm_mod_amount[i];
        ff>>pwm_centre[i];
    ///////////////////////////////////////////////////////////
        ff>>filter_type[i];
    ///////////////////////////////////////////////////////////
        ff>>cuttoff_slider_type[i];
        ff>>cutoff_mod_type[i];
        ff>>cutoff_mod_amount[i];
        ff>>center_cutoff[i];
        ff>>cutoff[i];
    ///////////////////////////////////////////////////////////
        ff>>resonance[i];
    ///////////////////////////////////////////////////////////
	}
	
    ///////////////////////////////////////////////////////////
    // Amp Envelopes //////////////////////////////////////////
	for(int i=0; i<envn; i++)
	{
		ff>>env[i].adsr.A.time;
		ff>>env[i].adsr.D.time;
		ff>>env[i].adsr.S.time;
		ff>>env[i].adsr.R.time;

		ff>>env[i].adsr.A.value;
		ff>>env[i].adsr.D.value;
		ff>>env[i].adsr.S.value;
		ff>>env[i].adsr.R.value;

		ff>>env_scale[i]; 

        ff>>env_slider_type[i];
        ff>>env_form[i];
        if(i<3) ff>>env_freerun[i];
	}

    ff>>radio_env_amp;
    ff>>radio_env_mod;

    ///////////////////////////////////////////////////////////
    // LFOs ///////////////////////////////////////////////////
	for(int i=0; i<lfos; i++)
	{
        ff>>lfo_form[i];
        ff>>lfo_mod_type[i];
        ff>>lfo_mod_amount[i];
        ff>>lfo[i].frequency;
    }

    ///////////////////////////////////////////////////////////
    // Sequencer //////////////////////////////////////////////
    
    ff>>trigger_sequence;
    ff>>tempo;
    ff>>beat;
    ff>>seed[0];
    ff>>seed[1];
    ff>>step[0];
    ff>>step[1];
    ff>>octaves;
    ff>>steps;

    ff>>direction[0];
    ff>>direction[1];

    ff>>algorhithm[0];
    ff>>algorhithm[1];

    int f=0;

	for(int i=0; i<nn; i++)
	{
		ff>>f;
        note_set[i] = f;
        f = 0;
		ff>>oct_set[i];
		ff>>oct[i];
    	ff>>note[i];
	}


    ff.close();
}

preset::preset()
{
        lfo_amp[0] = 0.5f;
        lfo_amp[1] = 0.5f;

        lfo[0].amplitude = &lfo_amp[0];
        lfo[1].amplitude = &lfo_amp[1];
        lfo[0].morph = &lfo_morph[0];
        lfo[1].morph = &lfo_morph[1];
        lfo[0].init(true);
        lfo[1].init(true);  
        lfo_imprint[0] = imprint(&lfo[0], 120, 1);
        lfo_imprint[1] = imprint(&lfo[1], 120, 1); 
		for(int i=0; i<nn; i++)
		{
			note[i]=0;
		}
		note[0] = 1;
        for(int osc=0; osc<oscn; osc++)
        {
            octave[osc] = 1;
        } 
		for(int i=0; i<envn; i++)
		{
			env_scale[i]=1.0f; 
		}
}

preset::~preset()
{
}

extern preset o;


