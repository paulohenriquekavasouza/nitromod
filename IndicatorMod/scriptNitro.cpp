/*
	EN: CREATED BY PAULO HENRIQUE KAVA DE SOUZA
	THIS MOD IS IN THE ALPHA STAGE AND DON'T REPRESENT THE MOD IN THE LAST STAGE.
	CREATED USING ALEXANDER BLADE'S CODE
	ONLY FOR GTA V. THIS SCRIPT ABLE YOU TO USE NITRO IN YOUR CAR.

	BRAZIL 2015

	PT-BR: CRIADO POR PAULO HENRIQUE KAVA DE SOUZA
	ESTE MOD ESTA EM SUA FASE ALPHA E NAO REPRESENTA O MOD EM ULTIMO ESTAGIO.
	CRIADO USANDO CODIGO DE ALEXANDER BLADE.
	SOMENTE PARA GTA V. ESTE SCRIPT POSSIBILITA VOCÊ USAR NITRO EM SEU CARRO.

	BRASIL 2015

*/

#include "scriptNitro.h"
#include "keyboard.h"
#include "../../inc/menu.h"

#include <string>
#include <tchar.h>
#include <time.h>
//#include <tlhelp32.h>

#pragma warning(disable : 4996)
#pragma warning(disable : 4244 4305)
#pragma warning(disable : 4067)
#pragma warning(disable : 4800)
//#pragma warning(disable : 4101)

#define DEVELOPER 0

using namespace std;

DWORD teclasSuportadas[22] = {
	VK_F1,
	VK_F2,
	VK_F3,
	VK_F4,
	VK_F5,
	VK_F6,
	VK_F7,
	VK_F8,
	VK_F9,
	VK_F10,
	VK_F11,
	VK_F12,
	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9
};

LPCSTR teclasDisponiveis[22] = {
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
	"NUMPAD0",
	"NUMPAD1",
	"NUMPAD2",
	"NUMPAD3",
	"NUMPAD4",
	"NUMPAD5",
	"NUMPAD6",
	"NUMPAD7",
	"NUMPAD8",
	"NUMPAD9"
};

string textosVoo[3] = {
	"VOO",
	"VOO INCRIVEL",
	"VOO EXTREMO"
};

void str_replace(char *target, const char *needle, const char *replacement) {
	char buffer[1024] = {0};
	char *insert_point = &buffer[0];
	const char *tmp = target;
	size_t needle_len = strlen(needle);
	size_t repl_len = strlen(replacement);

	while(1) {
		const char *p = strstr(tmp, needle);

		// walked past last occurrence of needle; copy remaining part
		if(p == NULL) {
			strcpy(insert_point, tmp);
			break;
		}

		// copy part before needle
		memcpy(insert_point, tmp, p - tmp);
		insert_point += p - tmp;

		// copy replacement string
		memcpy(insert_point, replacement, repl_len);
		insert_point += repl_len;

		// adjust pointers, move on
		tmp = p + needle_len;
	}

	// write altered string back to target
	strcpy(target, buffer);
}

/*HANDLE GetProcessHandle(const char *process_name, DWORD dwAccess) {
	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;


	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if(hProcessSnap == INVALID_HANDLE_VALUE) {
		return INVALID_HANDLE_VALUE;
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if(!Process32First(hProcessSnap, &pe32)) {
		return INVALID_HANDLE_VALUE;
	}

	do {
		if(strcmp(pe32.szExeFile, process_name) == 0)
			return OpenProcess(dwAccess, 0, pe32.th32ProcessID);

	} while(Process32Next(hProcessSnap, &pe32));

}*/

// KEYS AREA - START
bool key_pressed(DWORD keyV) {
	return IsKeyJustUp(keyV);
}
// KEYS AREA - END

// GRAPH AREA - START
void draw_rect(float A_0, float A_1, float A_2, float A_3, int A_4, int A_5, int A_6, int A_7) {
	GRAPHICS::DRAW_RECT((A_0 + (A_2 * 0.5f)), (A_1 + (A_3 * 0.5f)), A_2, A_3, A_4, A_5, A_6, A_7);
}

void draw_menu_lineNitro(std::string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool title, int r, int g, int b, int alpha, int fonte, float tamanhoFonte, bool rescaleText, bool textoPersonalizado) {
	// default values
	int text_col[4] = { r, g, b, alpha },
		rect_col[4] = { r, g, b, alpha };
	float text_scale = tamanhoFonte;
	int font = fonte;

	rect_col[0] = r;
	rect_col[1] = g;
	rect_col[2] = b;

	text_col[0] = r;
	text_col[1] = g;
	text_col[2] = b;

	// correcting values for active line
	if(active && !(textoPersonalizado)) {
		text_col[0] = r;
		text_col[1] = g;
		text_col[2] = b;

		rect_col[0] = r;
		rect_col[1] = g;
		rect_col[2] = b;

		if(rescaleText) text_scale = 0.40;
	}

	if(title && !(textoPersonalizado)) {
		rect_col[0] = r;
		rect_col[1] = g;
		rect_col[2] = b;

		if(rescaleText) text_scale = 0.50;
		font = fonte;
	}

	int screen_w, screen_h;
	GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

	textLeft += lineLeft;

	float lineWidthScaled = lineWidth / (float)screen_w; // line width
	float lineTopScaled = lineTop / (float)screen_h; // line top offset
	float textLeftScaled = textLeft / (float)screen_w; // text left offset
	float lineHeightScaled = lineHeight / (float)screen_h; // line height

	float lineLeftScaled = lineLeft / (float)screen_w;

	// this is how it's done in original scripts

	// text upper part
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0, text_scale);
	UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)caption.c_str());
	UI::_DRAW_TEXT(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));

	// text lower part
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0, text_scale);
	UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_GXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)caption.c_str());
	int num25 = UI::_0x9040DFB09BE75706(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));

	// rect
	draw_rect(lineLeftScaled, lineTopScaled + (0.00278f),
		lineWidthScaled, ((((float)(num25)* UI::_0xDB88A37483346780(text_scale, 0)) + (lineHeightScaled * 2.0f)) + 0.005f),
		rect_col[0], rect_col[1], rect_col[2], rect_col[3]);
}

std::string statusText;
DWORD statusTextDrawTicksMax;
bool statusTextGxtEntry;
int fonteTexto, rTexto, gTexto, bTexto, alphaTexto;
float tamanhoTexto, posXTexto, posYTexto;

void update_status_text() {
	if (GetTickCount() < statusTextDrawTicksMax) {
		UI::_DRAW_TEXT(posXTexto, posYTexto);
		UI::SET_TEXT_FONT(fonteTexto);
		UI::SET_TEXT_SCALE(tamanhoTexto, tamanhoTexto);
		UI::SET_TEXT_COLOUR(rTexto, gTexto, bTexto, alphaTexto);
		UI::SET_TEXT_WRAP(0.0, 1.0);
		UI::SET_TEXT_CENTRE(1);
		UI::SET_TEXT_DROPSHADOW(0.7, 0, 0, 0, 255);
		UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
		if (statusTextGxtEntry) {
			UI::_SET_TEXT_ENTRY((char *)statusText.c_str());
		} else {
			UI::_SET_TEXT_ENTRY("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING((char *)statusText.c_str());
		}
		UI::_DRAW_TEXT(posXTexto, posYTexto);
	}
}

void set_status_text(std::string str, DWORD time = 2500, bool isGxtEntry = false, int fonte = 1, float tamanho = 0.55, int r = 255, int g = 255, int b = 255, int alpha = 255, float posX = 0.5, float posY = 0.5) {
	statusText = str;
	statusTextDrawTicksMax = GetTickCount() + time;
	statusTextGxtEntry = isGxtEntry;
	fonteTexto = fonte;
	tamanhoTexto = tamanho;
	rTexto = r;
	gTexto = g;
	bTexto = b;
	alphaTexto = alpha;
	posXTexto = posX;
	posYTexto = posY;
}

void update_features() {
	update_status_text();
}

// GRAPH AREA - END

// VARIABLES
// READING KEY FROM nitroMod.ini FILE
LPCSTR versao = "2.0";
LPCSTR build = "202112121124";//"121120171204";
LPCSTR arquivo = "nitroMod.ini";
LPCSTR path = ".\\nitroMod.ini";
LPCSTR arquivoDev = "nitroMod.dev";
LPCSTR arquivoLog = "nitroModLog.txt";

std::string nomeMod = "NitroMod";

DWORD keyActiveMod = VK_F5;
DWORD keySavePosition = VK_NUMPAD9;
DWORD keyFunMod = VK_NUMPAD1;
DWORD keyMenu = VK_F11;

bool scriptStarted = false;
bool devModeOn = false;
bool arquivoEncontrado = false;
bool selecionouTeclaArquivo = false;
bool autoAtivacao = false;
bool primeiroUso = false;
bool mostrouErroOnline = false;
bool nitroInfinito = false;
bool allVehicles = false;
bool efetuouTela = false;
//bool efetuouSom = false;
bool efeitoTela = true;
bool efeitoSom = true;
bool usandoW = true;
bool editandoPosicao = false;
bool pegouPosicao = false;
bool modoFun = false;
bool showNumberNitroBar = true;
bool shakeJoystick = true;
bool isPlayerOnline = false;
bool proximaAtivacaoManual = false;
bool estaNaContramao = false;
bool velocidadeAcimaBonus = false;
bool podeMudarVelocidade = false;
bool bonus = true;

float maxNitro = 100.0; // 100.0
float valorNitro = maxNitro;
float maxVel = 300.0;
float minVelLimite = 100.0; //(devModeOn) ? 0.0 : 100.0;
float maxVelLimite = 300.0; //(devModeOn) ? 539.0 : 300.0;
float nitroPorCiclo = 0.70; // 1 = PADRAO
float nitroPorCicloPadrao = nitroPorCiclo;
float nitroRemovido = 0.45; // 2
float nitroRemovidoPadrao = nitroRemovido;
float nitroPorCicloContraMao = 2;
float nitroPorCicloVelocidade = 1.15;
float nitroPorCicloSomadoTodosBonus = nitroPorCicloContraMao + nitroPorCicloVelocidade;
float posX = 690.0;
float posY = 250.0;
float baseCalculo = 2.0;
float flameMultiplier = 1.0;
float kilometerConvert = 3.6;
float novaVelocidadeVar = maxVel;
float calculoVelocidadeAcimaBonus = ((maxVel / 2) + 20);

int rArquivo = 0;
int gArquivo = 0;
int bArquivo = 255;
int valorTimer = 0;
int valorTimerNitroMax = 40; // 16 = PADRAO - 40 = BOM
int valorTimerNitroMaxPadrao = valorTimerNitroMax;
int tempoContramao = 0;
int minTempoContramao = 1100;
int activeLineIndexMain = 0;

Player playerPedId, veiculoAntigo;
Vehicle veiculo, carroPlayer;

char teclaPosicao[64];
char textoLog[5012];

char* dataHoraAtual() {
	time_t     now = time(0);
	struct tm  tstruct;
	tstruct = *localtime(&now);
	char textDataHora[255];
	strftime(textDataHora, sizeof(textDataHora), "%d/%m/%Y %H:%M:%S", &tstruct);

	return textDataHora;
	
}

void salvaLog(char* logRecebido) {
	FILE *file;
	file = fopen(arquivoLog, "a+");
	if(file != NULL) {
		fputs(logRecebido, file);
		fclose(file);
	}
}

char* pegaWindowsVersao(char* buildWindows) {
	char retorno[255];

	if(strcmp(_T(buildWindows), "6001") == 0) {
		sprintf_s(retorno, "SP1");
	} else if(strcmp(_T(buildWindows), "6002") == 0) {
		sprintf_s(retorno, "SP2");
	} else if(strcmp(_T(buildWindows), "7601") == 0) {
		sprintf_s(retorno, "SP1");
	} else if(strcmp(_T(buildWindows), "9600") == 0) {
		sprintf_s(retorno, "(Update 1)");
	} else if(strcmp(_T(buildWindows), "10586") == 0) {
		sprintf_s(retorno, "(1511)");
	} else if(strcmp(_T(buildWindows), "10586") == 0) {
		sprintf_s(retorno, "(1607)");
	} else if(strcmp(_T(buildWindows), "15063") == 0) {
		sprintf_s(retorno, "(1703)");
	} else if(strcmp(_T(buildWindows), "16299") == 0) {
		sprintf_s(retorno, "(1709)");
	} else {
		sprintf_s(retorno, "");
	}

	return retorno;
}

void mostraTextoEsquerda(char* texto) {
	UI::_SET_TEXT_COMPONENT_FORMAT("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(texto);
	UI::_DISPLAY_HELP_TEXT_FROM_STRING_LABEL(0, 0, 1, -1);
}

void show_notification(char* msg, char* picName1, char* picName2, char* sender, char* subject) {
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(msg);
	UI::_SET_NOTIFICATION_MESSAGE(picName1, picName2, false, 1, sender, subject);
	UI::_DRAW_NOTIFICATION(FALSE, TRUE);
}

void mostraTextoInicial(bool usandoWArq) {

	char text[256], text2[256];
	if(usandoWArq) {
		sprintf_s(text, "You're using ~b~%s ~w~v~g~%s~w~.\nEnjoy!", nomeMod, versao);
		sprintf_s(text2, "~w~Hold ~INPUT_SPRINT~+~INPUT_MOVE_UP_ONLY~ ~w~or ~g~A~w~ to use Nitro.");
	} else {
		sprintf_s(text, "You're using ~b~%s ~w~v~g~%s~w~.\nEnjoy!", nomeMod, versao);
		sprintf_s(text2, "~w~Hold ~INPUT_SPRINT~ ~w~or ~g~A ~w~to use Nitro.");
	}

	mostraTextoEsquerda(text2);

	char nomeModT[64];
	sprintf_s(nomeModT, "~y~%s", nomeMod);
	show_notification(text, "CHAR_DEFAULT", "CHAR_DEFAULT", nomeModT, "Developed by ~b~PhK");

}

void menu_beep(int tipo = 1) {
	if(tipo == 1) {
		AUDIO::PLAY_SOUND_FRONTEND(-1, "CHECKPOINT_UNDER_THE_BRIDGE", "HUD_MINI_GAME_SOUNDSET", 0);
	} else {
		AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_LIQUOR_STORE_SOUNDSET", 1);
	}
}

void desativaMod() {
	scriptStarted = false;
	if(autoAtivacao) {
		proximaAtivacaoManual = true;
	}
	char text[256];
	sprintf_s(text, "~b~%s ~w~deactivated. Thanks for using it :).", nomeMod);
	char nomeModT[64];
	sprintf_s(nomeModT, "~y~%s", nomeMod);
	show_notification(text, "CHAR_DEFAULT", "CHAR_DEFAULT", nomeModT, "Developed by ~b~PhK");
	menu_beep();
	WAIT(0);
}

void verificaArquivo() {
	FILE *file;
	file = fopen(arquivo, "r");
	//if(scriptStarted) {
		if(file == NULL) {
			char text[255];
			sprintf_s(text, "[%s] %s ~r~not found~w~.\nExiting mod...", nomeMod, arquivo);
			scriptStarted = false;
			arquivoEncontrado = false;
			desativaMod();			
		} else {
			arquivoEncontrado = true;

			if(selecionouTeclaArquivo == false) {
				char realKeyMod[32];
				GetPrivateProfileString(_T("CONFIGURATION"), _T("activateKeyScript"), _T(""), _T(realKeyMod), 32, path);

				for(int i = 0; i < 22; i++) {
					if(strcmp(_T(realKeyMod), teclasDisponiveis[i]) == 0) {
						keyActiveMod = teclasSuportadas[i];
					}
				}

				char realKeySave[32];
				GetPrivateProfileString(_T("CONFIGURATION"), _T("saveActualPosition"), _T(""), _T(realKeySave), 32, path);

				for(int i = 0; i < 22; i++) {
					if(strcmp(_T(realKeySave), teclasDisponiveis[i]) == 0) {
						keySavePosition = teclasSuportadas[i];
						sprintf_s(teclaPosicao, "%s", teclasDisponiveis[i]);
					}
				}

				char realKeyFun[32];
				GetPrivateProfileString(_T("CONFIGURATION"), _T("funMode"), _T(""), _T(realKeyFun), 32, path);

				for(int i = 0; i < 22; i++) {
					if(strcmp(_T(realKeyFun), teclasDisponiveis[i]) == 0) {
						keyFunMod = teclasSuportadas[i];
					}
				}
				selecionouTeclaArquivo = true;
			}

			char bonusChar[32];
			GetPrivateProfileString(_T("CONFIGURATION"), _T("bonus"), _T(""), _T(bonusChar), 32, path);

			if (strcmp(_T(bonusChar), "1") == 0) {
				bonus = true;
			} else {
				bonus = false;
			}

			char infiniteNitro[32];
			GetPrivateProfileString(_T("CONFIGURATION"), _T("infiniteNitro"), _T(""), _T(infiniteNitro), 32, path);

			if(strcmp(_T(infiniteNitro), "1") == 0) {
				nitroInfinito = true;
			} else {
				nitroInfinito = false;
			}

			char autoAtivacaoChar[32];
			GetPrivateProfileString(_T("CONFIGURATION"), _T("autoActive"), _T(""), _T(autoAtivacaoChar), 32, path);

			if(strcmp(_T(autoAtivacaoChar), "1") == 0) {
				autoAtivacao = true;
			} else {
				autoAtivacao = false;
			}

			char showNumberNitro[32];
			GetPrivateProfileString(_T("CONFIGURATION"), _T("showNitroValue"), _T(""), _T(showNumberNitro), 32, path);

			if(strcmp(_T(showNumberNitro), "1") == 0) {
				showNumberNitroBar = true;
			} else {
				showNumberNitroBar = false;
			}

			char shakeJoystickChar[32];
			GetPrivateProfileString(_T("CONFIGURATION"), _T("shakeJoystick"), _T(""), _T(shakeJoystickChar), 32, path);

			if(strcmp(_T(shakeJoystickChar), "1") == 0) {
				shakeJoystick = true;
			} else {
				shakeJoystick = false;
			}

			char velocidadeMaxima[32];
			GetPrivateProfileString(_T("CONFIGURATION"), _T("maxVel"), _T(""), _T(velocidadeMaxima), 32, path);

			maxVel = atof(velocidadeMaxima);

			char multiplicadorChama[32];
			GetPrivateProfileString(_T("CONFIGURATION"), _T("flameMultiplier"), _T(""), _T(multiplicadorChama), 32, path);

			flameMultiplier = atof(multiplicadorChama);

			if(pegouPosicao == false) {
				char posicaoXArquivo[32];
				GetPrivateProfileString(_T("CONFIGURATION"), _T("posX"), _T(""), _T(posicaoXArquivo), 32, path);

				posX = atof(posicaoXArquivo);

				char posicaoYArquivo[32];
				GetPrivateProfileString(_T("CONFIGURATION"), _T("posY"), _T(""), _T(posicaoYArquivo), 32, path);

				posY = atof(posicaoYArquivo);

				pegouPosicao = true;
			}

			if(modoFun == false) {
				char rArquivoChar[32];
				GetPrivateProfileString(_T("CONFIGURATION"), _T("barRed"), _T(""), _T(rArquivoChar), 32, path);

				rArquivo = atoi(rArquivoChar);

				char gArquivoChar[32];
				GetPrivateProfileString(_T("CONFIGURATION"), _T("barGreen"), _T(""), _T(gArquivoChar), 32, path);

				gArquivo = atoi(gArquivoChar);

				char bArquivoChar[32];
				GetPrivateProfileString(_T("CONFIGURATION"), _T("barBlue"), _T(""), _T(bArquivoChar), 32, path);

				bArquivo = atoi(bArquivoChar);
			}

			char efeitoTelaChar[32];
			GetPrivateProfileString(_T("CONFIGURATION"), _T("screenEffect"), _T(""), _T(efeitoTelaChar), 32, path);

			if(strcmp(_T(efeitoTelaChar), "1") == 0) {
				efeitoTela = true;
			} else {
				efeitoTela = false;
			}

			char efeitoSomChar[32];
			GetPrivateProfileString(_T("CONFIGURATION"), _T("soundEffect"), _T(""), _T(efeitoSomChar), 32, path);

			if(strcmp(_T(efeitoSomChar), "1") == 0) {
				efeitoSom = true;
			} else {
				efeitoSom = false;
			}

			char wKeyChar[32];
			GetPrivateProfileString(_T("CONFIGURATION"), _T("useWKey"), _T(""), _T(wKeyChar), 32, path);

			if(strcmp(_T(wKeyChar), "1") == 0) {
				usandoW = true;
			} else {
				usandoW = false;
			}

			char allVehiclesChar[32];
			GetPrivateProfileString(_T("CONFIGURATION"), _T("allVehicles"), _T(""), _T(allVehiclesChar), 32, path);

			if(strcmp(_T(allVehiclesChar), "1") == 0) {
				allVehicles = true;
			} else {
				allVehicles = false;
			}

		}
		fclose(file);
		WAIT(0);
	//}
}

void notifyAboveMap(char* msg) {
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(msg);
	UI::_DRAW_NOTIFICATION(FALSE, FALSE);
}

void bottomPrint(char* text, int msecToDisplay) {
	UI::_SET_TEXT_ENTRY_2("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_DRAW_SUBTITLE_TIMED(msecToDisplay, true);
}

void StartLoadingMessage(char *text, int spinnerType = 3) {
	UI::_0xABA17D7CE615ADBF("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_0xBD12F8228410D9B4(spinnerType);
}

void som_nitro() {

	if(IsKeyDown(VK_SHIFT) || CONTROLS::IS_CONTROL_PRESSED(2, 86)) {
		AUDIO::SET_VEHICLE_BOOST_ACTIVE(carroPlayer, true);

		/*HANDLE hProcess = GetProcessHandle("nitroSound.exe", PROCESS_QUERY_INFORMATION);
		if(hProcess == 0 || hProcess == INVALID_HANDLE_VALUE) {
			if(efetuouSom == false) {
				ShellExecute(NULL, "open", "nitroSound.exe", NULL, NULL, SW_SHOWDEFAULT);
				efetuouSom = true;
			}
		} else {
			efetuouSom = true;
		}*/
	} else {
		AUDIO::SET_VEHICLE_BOOST_ACTIVE(carroPlayer, false);
	}
}

void tremeControle() {
	if(shakeJoystick) {
		CONTROLS::SET_PAD_SHAKE(0, 200, 250);
	}
}

void mostraNitro() {

	float tamanhoBarraHeight = 2.5;
	float tamanhoBarraBackground = 0.0; //(showNumberNitroBar && !estaNaContramao) ? 12.0 : 5.5;
	if(estaNaContramao && velocidadeAcimaBonus && valorNitro < maxNitro-1 && bonus) {
		if(showNumberNitroBar) {
			tamanhoBarraBackground = 30.0;
		} else {
			tamanhoBarraBackground = 20.0;
		}
	} else if(estaNaContramao && !velocidadeAcimaBonus && valorNitro < maxNitro - 1 && bonus) {
		if(showNumberNitroBar) {
			tamanhoBarraBackground = 20.0;
		} else {
			tamanhoBarraBackground = 12.0;
		}
	} else if(!estaNaContramao && velocidadeAcimaBonus && valorNitro < maxNitro - 1 && bonus) {
		if(showNumberNitroBar) {
			tamanhoBarraBackground = 20.0;
		} else {
			tamanhoBarraBackground = 12.0;
		}
	} else {
		if(showNumberNitroBar) {
			tamanhoBarraBackground = 12.0;
		} else {
			tamanhoBarraBackground = 5.5;
		}
	}

	//UI::SET_ABILITY_BAR_VALUE(valorNitro, maxNitro);

	if(!ENTITY::IS_ENTITY_DEAD(playerPedId) && VEHICLE::IS_VEHICLE_DRIVEABLE(veiculo, true)) {

		if(allVehicles == false) {
			if(!(PED::IS_PED_IN_ANY_PLANE(playerPedId)) && !(PED::IS_PED_IN_ANY_HELI(playerPedId)) && !(PED::IS_PED_IN_ANY_BOAT(playerPedId)) && !(PED::IS_PED_IN_ANY_TRAIN(playerPedId))) {
				draw_menu_lineNitro("", maxNitro + 4.0f, tamanhoBarraBackground, posX - 2.0f, posY - 2.0f, 1.0, true, false, 0, 0, 0, 50, 1, 0.30, true, true);
				draw_menu_lineNitro("", maxNitro, tamanhoBarraHeight, posX, posY, 1.0, true, false, 0, 0, 0, 90, 1, 0.30, true, true);

				if(valorNitro >= 50 && modoFun == false) {
					draw_menu_lineNitro("", valorNitro, tamanhoBarraHeight, posX, posY, 1.0, true, false, rArquivo, gArquivo, bArquivo, 255, 1, 0.30, true, true);
				} else if(valorNitro < 50 && valorNitro >= 25 && modoFun == false) {
					draw_menu_lineNitro("", valorNitro, tamanhoBarraHeight, posX, posY, 1.0, true, false, 255, 215, 0, 255, 1, 0.30, true, true);
				} else if(valorNitro < 25 && modoFun == false) {
					draw_menu_lineNitro("", valorNitro, tamanhoBarraHeight, posX, posY, 1.0, true, false, 255, 0, 0, 255, 1, 0.30, true, true);
				} else if(modoFun) {
					draw_menu_lineNitro("", valorNitro, tamanhoBarraHeight, posX, posY, 1.0, true, false, rArquivo, gArquivo, bArquivo, 255, 1, 0.30, true, true);
				}

				if(showNumberNitroBar) {
					char valorNitroAtualChar[255];
					sprintf_s(valorNitroAtualChar, "%6.0lf* +%1.2lfx/c -%1.2lfx/c", valorNitro, nitroPorCiclo, nitroRemovido);
					str_replace(valorNitroAtualChar, "*", "%");

					draw_menu_lineNitro(valorNitroAtualChar, 0.0, tamanhoBarraHeight, posX + 8.0f, posY - 9.5f, 1.0, true, false, 255, 255, 255, 255, 4, 0.40, true, true);
					//draw_menu_lineNitro(valorNitroAtualChar, 0.0, tamanhoBarraHeight, posX + 8.0f, ((posY + (maxNitro / 2)) - (maxNitro / 2)), 1.0, true, false, 255, 255, 255, 255, 4, 0.40, true, true);
				}
				if(estaNaContramao && velocidadeAcimaBonus && valorNitro < maxNitro - 1 && bonus) {
					char textoEstaNaContramao[255];
					sprintf_s(textoEstaNaContramao, "~r~WRONG WAY ~y~BONUS~w~!\n~g~SPEED ~y~BONUS~w~!");
					float posXFinal = (showNumberNitroBar) ? posX + 22.0f : posX + 8.0f;
					draw_menu_lineNitro(textoEstaNaContramao, 0.0, tamanhoBarraHeight, posXFinal, posY + 6.0f, 1.0, true, false, 255, 255, 255, 255, 4, 0.40, true, true);
				} else if(estaNaContramao && !velocidadeAcimaBonus && valorNitro < maxNitro - 1 && bonus) {
					char textoEstaNaContramao[255];
					sprintf_s(textoEstaNaContramao, "~r~WRONG WAY ~y~BONUS~w~!");
					float posXFinal = (showNumberNitroBar) ? posX + 22.0f : posX + 8.0f;
					draw_menu_lineNitro(textoEstaNaContramao, 0.0, tamanhoBarraHeight, posXFinal, posY + 6.0f, 1.0, true, false, 255, 255, 255, 255, 4, 0.40, true, true);
				} else if(!estaNaContramao && velocidadeAcimaBonus && valorNitro < maxNitro - 1 && bonus) {
					char textoEstaNaContramao[255];
					sprintf_s(textoEstaNaContramao, "~g~SPEED ~y~BONUS~w~!");
					float posXFinal = (showNumberNitroBar) ? posX + 22.0f : posX + 8.0f;
					draw_menu_lineNitro(textoEstaNaContramao, 0.0, tamanhoBarraHeight, posXFinal, posY + 6.0f, 1.0, true, false, 255, 255, 255, 255, 4, 0.40, true, true);
				}
			}
		} else {
			draw_menu_lineNitro("", maxNitro + 4.0f, tamanhoBarraBackground, posX - 2.0f, posY - 2.0f, 1.0, true, false, 0, 0, 0, 50, 1, 0.30, true, true);
			draw_menu_lineNitro("", maxNitro, tamanhoBarraHeight, posX, posY, 1.0, true, false, 0, 0, 0, 120, 1, 0.30, true, true);

			if(valorNitro >= 50 && modoFun == false) {
				draw_menu_lineNitro("", valorNitro, tamanhoBarraHeight, posX, posY, 1.0, true, false, rArquivo, gArquivo, bArquivo, 255, 1, 0.30, true, true);
			} else if(valorNitro < 50 && valorNitro >= 25 && modoFun == false) {
				draw_menu_lineNitro("", valorNitro, tamanhoBarraHeight, posX, posY, 1.0, true, false, 255, 215, 0, 255, 1, 0.30, true, true);
			} else if(valorNitro < 25 && modoFun == false) {
				draw_menu_lineNitro("", valorNitro, tamanhoBarraHeight, posX, posY, 1.0, true, false, 255, 0, 0, 255, 1, 0.30, true, true);
			} else if(modoFun) {
				draw_menu_lineNitro("", valorNitro, tamanhoBarraHeight, posX, posY, 1.0, true, false, rArquivo, gArquivo, bArquivo, 255, 1, 0.30, true, true);
			}

			if(showNumberNitroBar) {
				char valorNitroAtualChar[255];
				sprintf_s(valorNitroAtualChar, "%6.0lf* +%1.2lfx/c -%1.2lfx/c", valorNitro, nitroPorCiclo, nitroRemovido);
				str_replace(valorNitroAtualChar, "*", "%");

				draw_menu_lineNitro(valorNitroAtualChar, 0.0, tamanhoBarraHeight, posX + 8.0f, posY - 9.5f, 1.0, true, false, 255, 255, 255, 255, 4, 0.40, true, true);
				//draw_menu_lineNitro(valorNitroAtualChar, 0.0, tamanhoBarraHeight, posX + 8.0f, ((posY + (maxNitro / 2)) - (maxNitro/2)), 1.0, true, false, 255, 255, 255, 255, 4, 0.40, true, true);
			}
			if(estaNaContramao && velocidadeAcimaBonus && valorNitro < maxNitro-1 && bonus) {
				char textoEstaNaContramao[255];
				sprintf_s(textoEstaNaContramao, "~r~WRONG WAY ~y~BONUS~w~!\n~g~SPEED ~y~BONUS~w~!");
				float posXFinal = (showNumberNitroBar) ? posX + 22.0f : posX + 8.0f;
				draw_menu_lineNitro(textoEstaNaContramao, 0.0, tamanhoBarraHeight, posXFinal, posY + 6.0f, 1.0, true, false, 255, 255, 255, 255, 4, 0.40, true, true);
			} else if(estaNaContramao && !velocidadeAcimaBonus && valorNitro < maxNitro - 1 && bonus) {
				char textoEstaNaContramao[255];
				sprintf_s(textoEstaNaContramao, "~r~WRONG WAY ~y~BONUS~w~!");
				float posXFinal = (showNumberNitroBar) ? posX + 22.0f : posX + 8.0f;
				draw_menu_lineNitro(textoEstaNaContramao, 0.0, tamanhoBarraHeight, posXFinal, posY + 6.0f, 1.0, true, false, 255, 255, 255, 255, 4, 0.40, true, true);
			} else if(!estaNaContramao && velocidadeAcimaBonus && valorNitro < maxNitro - 1 && bonus) {
				char textoEstaNaContramao[255];
				sprintf_s(textoEstaNaContramao, "~g~SPEED ~y~BONUS~w~!");
				float posXFinal = (showNumberNitroBar) ? posX + 22.0f : posX + 8.0f;
				draw_menu_lineNitro(textoEstaNaContramao, 0.0, tamanhoBarraHeight, posXFinal, posY + 6.0f, 1.0, true, false, 255, 255, 255, 255, 4, 0.40, true, true);
			}
		}
	}
}

void encheNitro() {
	valorTimer++;

	char valorNitroChar[32];	

	if(valorNitro < maxNitro && !(IsKeyDown(VK_SHIFT)) && !(CONTROLS::IS_CONTROL_PRESSED(2, 86)) && valorTimer >= valorTimerNitroMax) {
		valorNitro += nitroPorCiclo;

		sprintf_s(valorNitroChar, "%f", valorNitro);

		valorTimer = 0;

		/*if(!(key_pressed(VK_SHIFT)) && !(IsKeyDown(VK_SHIFT)) && !(CONTROLS::IS_CONTROL_PRESSED(0, 0xBF))) 
			if(efetuouSom)
				efetuouSom = false;*/
	}
	efetuouTela = false;
	mostraNitro();
}

void executaNitro() {

	if(scriptStarted) {
		if(modoFun) {
			float velocidade = ENTITY::GET_ENTITY_SPEED(veiculo);			
			float velocidadeKmh = velocidade*kilometerConvert;
			float velocidadeAdicionada = 0.02f;

			velocidade += velocidade*velocidadeAdicionada;
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(veiculo, velocidade);
		} else {
			// NOVA FORMA DE ACELERAR O VEICULO
			VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(veiculo, 120.0);
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(veiculo, 120.0);
		}

		if(!nitroInfinito)
			valorNitro -= nitroRemovido; // 2

		if(efetuouTela == false && efeitoTela && PLAYER::IS_PLAYER_DEAD(playerPedId) == false) {
			GRAPHICS::_START_SCREEN_EFFECT("RaceTurbo", 0, 0);
			CONTROLS::DISABLE_CONTROL_ACTION(0, 77, true);

			efetuouTela = true;
		}
		if(efeitoSom && PLAYER::IS_PLAYER_DEAD(playerPedId) == false) {
			som_nitro();

			AUDIO::SET_VEHICLE_BOOST_ACTIVE(carroPlayer, false);
			efetuouTela = true;
		}
		char* escapamentos[7] = {
			"exhaust",
			"exhaust_2",
			"exhaust_3",
			"exhaust_4",
			"exhaust_5",
			"exhaust_6",
			"exhaust_7"
		};

		if(STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_carsteal4")) {
			float direction = ENTITY::GET_ENTITY_HEADING(carroPlayer);
			float pitch = ENTITY::GET_ENTITY_PITCH(carroPlayer);

			for(int i = 0; i < 7; i++) {
				Vector3 offset = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(carroPlayer, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(carroPlayer, escapamentos[i]));
				GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_carsteal4");
				GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_carsteal5_car_muzzle_flash", offset.x, offset.y, offset.z, 0.0f, pitch, direction - 90.0f, flameMultiplier, false, false, false);
			}			
		} else {
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_carsteal4");
		}		

		mostraNitro();
		update_features();
	}
}

void nitroFunction() {

	if(isPlayerOnline && !mostrouErroOnline) {
		desativaMod();
	}

	if(scriptStarted && ENTITY::DOES_ENTITY_EXIST(playerPedId) && PLAYER::IS_PLAYER_DEAD(playerPedId) == false && PED::IS_PED_IN_VEHICLE(playerPedId, PLAYER::GET_PLAYERS_LAST_VEHICLE(), 0)) {				

		float velocidade = ENTITY::GET_ENTITY_SPEED(veiculo);		
		float velocidadeKmh = velocidade*kilometerConvert;
		
		if(allVehicles == false) {
			if(!(PED::IS_PED_IN_ANY_PLANE(playerPedId)) && !(PED::IS_PED_IN_ANY_HELI(playerPedId)) && !(PED::IS_PED_IN_ANY_BOAT(playerPedId)) && !(PED::IS_PED_IN_ANY_TRAIN(playerPedId))) {
				if(usandoW) {
					if(IsKeyDown(VK_SHIFT) && IsKeyDown(0x57) && valorNitro >= 1 && velocidade > 1 && !(ENTITY::IS_ENTITY_IN_AIR(veiculo)) && VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(veiculo) && velocidadeKmh <= maxVel) {
						if(autoAtivacao && primeiroUso == false) {
							if(usandoW) {
								mostraTextoInicial(true);
							} else {
								mostraTextoInicial(false);
							}
							primeiroUso = true;
						}
						executaNitro();
					}
					if(CONTROLS::IS_CONTROL_PRESSED(0, 0xBF) && valorNitro >= 1 && velocidade > 1 && !(ENTITY::IS_ENTITY_IN_AIR(veiculo)) && VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(veiculo) && velocidadeKmh <= maxVel) {
						if(autoAtivacao && primeiroUso == false) {
							if(usandoW) {
								mostraTextoInicial(true);
							} else {
								mostraTextoInicial(false);
							}
							primeiroUso = true;
						}
						tremeControle();
						executaNitro();
					}
				} else {
					if(IsKeyDown(VK_SHIFT) && valorNitro >= 1 && velocidade > 1 && !(ENTITY::IS_ENTITY_IN_AIR(veiculo)) && VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(veiculo) && velocidadeKmh <= maxVel) {
						if(autoAtivacao && primeiroUso == false) {
							if(usandoW) {
								mostraTextoInicial(true);
							} else {
								mostraTextoInicial(false);
							}
							primeiroUso = true;
						}
						executaNitro();
					}
					if(CONTROLS::IS_CONTROL_PRESSED(0, 0xBF) && valorNitro >= 1 && velocidade > 1 && !(ENTITY::IS_ENTITY_IN_AIR(veiculo)) && VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(veiculo) && velocidadeKmh <= maxVel) {
						if(autoAtivacao && primeiroUso == false) {
							if(usandoW) {
								mostraTextoInicial(true);
							} else {
								mostraTextoInicial(false);
							}
							primeiroUso = true;
						}
						tremeControle();
						executaNitro();
					}
				}
			}
		} else {
			if(usandoW) {
				if(IsKeyDown(VK_SHIFT) && IsKeyDown(0x57) && valorNitro >= 1 && velocidade > 1 && !(ENTITY::IS_ENTITY_IN_AIR(veiculo)) && VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(veiculo) && VEHICLE::IS_VEHICLE_DRIVEABLE(veiculo, true) && velocidadeKmh <= maxVel) {
					if(autoAtivacao && primeiroUso == false) {
						if(usandoW) {
							mostraTextoInicial(true);
						} else {
							mostraTextoInicial(false);
						}
						primeiroUso = true;
					}
					executaNitro();
				}
				if(CONTROLS::IS_CONTROL_PRESSED(0, 0xBF) && valorNitro >= 1 && velocidade > 1 && !(ENTITY::IS_ENTITY_IN_AIR(veiculo)) && VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(veiculo) && VEHICLE::IS_VEHICLE_DRIVEABLE(veiculo, true) && velocidadeKmh <= maxVel) {
					if(autoAtivacao && primeiroUso == false) {
						if(usandoW) {
							mostraTextoInicial(true);
						} else {
							mostraTextoInicial(false);
						}
						primeiroUso = true;
					}
					tremeControle();
					executaNitro();
				}
			} else {
				if(IsKeyDown(VK_SHIFT) && valorNitro >= 1 && velocidade > 1 && !(ENTITY::IS_ENTITY_IN_AIR(veiculo)) && VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(veiculo) && VEHICLE::IS_VEHICLE_DRIVEABLE(veiculo, true) && velocidadeKmh <= maxVel) {
					if(autoAtivacao && primeiroUso == false) {
						if(usandoW) {
							mostraTextoInicial(true);
						} else {
							mostraTextoInicial(false);
						}
						primeiroUso = true;
					}
					executaNitro();
				}
				if(CONTROLS::IS_CONTROL_PRESSED(0, 0xBF) && valorNitro >= 1 && velocidade > 1 && !(ENTITY::IS_ENTITY_IN_AIR(veiculo)) && VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(veiculo) && VEHICLE::IS_VEHICLE_DRIVEABLE(veiculo, true) && velocidadeKmh <= maxVel) {
					if(autoAtivacao && primeiroUso == false) {
						if(usandoW) {
							mostraTextoInicial(true);
						} else {
							mostraTextoInicial(false);
						}
						primeiroUso = true;
					}
					tremeControle();
					executaNitro();
				}
			}
		}
		VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(veiculo, 1.0);
		encheNitro();

	}
}

void ativaMod() {
	if(proximaAtivacaoManual == false) {
		scriptStarted = true;

		if(autoAtivacao == false) {
			if(usandoW) {
				mostraTextoInicial(true);
			} else {
				mostraTextoInicial(false);
			}
		}
	}	
	//menu_beep();
}

void mostraTextoVelocidadeEditar() {
	char veloChar[256];
	sprintf_s(veloChar, "%6.0lf", novaVelocidadeVar);
	bottomPrint(veloChar, 100);

	notifyAboveMap("Press ~b~4 ~w~to ~r~decrease~w~, ~b~6 ~w~to ~g~increase~w~ and ~y~5 ~w~to ~g~save.");
}

void novaVelocidade() {	
	char veloChar[256];

	while(podeMudarVelocidade && !editandoPosicao) {
		mostraTextoVelocidadeEditar();
		if(IsKeyDown(VK_NUMPAD4)) {
			if(novaVelocidadeVar > minVelLimite) {
				novaVelocidadeVar--;

				AUDIO::PLAY_SOUND_FRONTEND(-1, "PIN_BUTTON", "ATM_SOUNDS", 1);

				sprintf_s(veloChar, "%6.0lf", novaVelocidadeVar);
				/*bottomPrint(veloChar, 5000);

				notifyAboveMap("Press ~b~4 ~w~to ~r~decrease~w~, ~b~6 ~w~to ~g~increase~w~ and ~y~5 ~w~to ~g~save.");*/
			} else if(novaVelocidadeVar < minVelLimite) {
				novaVelocidadeVar = minVelLimite;
			}
		}
		if(IsKeyDown(VK_NUMPAD6)) {
			if(novaVelocidadeVar < maxVelLimite) {
				novaVelocidadeVar++;

				AUDIO::PLAY_SOUND_FRONTEND(-1, "PIN_BUTTON", "ATM_SOUNDS", 1);

				sprintf_s(veloChar, "%6.0lf", novaVelocidadeVar);
				/*bottomPrint(veloChar, 5000);

				notifyAboveMap("Press ~b~4 ~w~to ~r~decrease~w~, ~b~6 ~w~to ~g~increase~w~ and ~y~5 ~w~to ~g~save.");*/
			} else if(novaVelocidadeVar > maxVelLimite) {
				novaVelocidadeVar = maxVelLimite;
			}
		}
		if(key_pressed(VK_NUMPAD5)) {
			if(novaVelocidadeVar <= minVelLimite) {
				novaVelocidadeVar = minVelLimite;
			} else if(novaVelocidadeVar > maxVelLimite) {
				novaVelocidadeVar = maxVelLimite;
			}
			AUDIO::PLAY_SOUND_FRONTEND(-1, "PIN_BUTTON", "ATM_SOUNDS", 1);

			sprintf_s(veloChar, "%3.1lf", novaVelocidadeVar);
			//bottomPrint(veloChar, 5000);

			WritePrivateProfileString(_T("CONFIGURATION"), _T("maxVel"), _T(veloChar), path);
			maxVel = novaVelocidadeVar;

			podeMudarVelocidade = false;
		}
		WAIT(0);
	}
}

void abreMenuConfigs() {
	//if(scriptStarted) {
		const float lineWidth = 250.0;
		const int lineCount = 9;

		std::string caption = "     " + nomeMod + " v." + versao;

		string lineCaption[lineCount] = {
			"Use W Key",
			"Screen Effect",
			"Sound Effect",
			"Infinite Nitro",
			"Show Nitro Value",
			"Shake Joystick",
			"All Vehicles",
			"Speed Limit",
			"Bonus Points"
		};

		DWORD waitTime = 150;
		while(true) {
			(usandoW) ? lineCaption[0] = "Use W Key                < ON >" : lineCaption[0] = "Use W Key                < OFF >";
			(efeitoTela) ? lineCaption[1] = "Screen Effect            < ON >" : lineCaption[1] = "Screen Effect            < OFF >";
			(efeitoSom) ? lineCaption[2] = "Sound Effect             < ON >" : lineCaption[2] = "Sound Effect             < OFF >";
			(nitroInfinito) ? lineCaption[3] = "Infinite Nitro              < ON >" : lineCaption[3] = "Infinite Nitro              < OFF >";
			(showNumberNitroBar) ? lineCaption[4] = "Show Nitro Value      < ON >" : lineCaption[4] = "Show Nitro Value      < OFF >";
			(shakeJoystick) ? lineCaption[5] = "Shake Joystick         < ON >" : lineCaption[5] = "Shake Joystick         < OFF >";
			(allVehicles) ? lineCaption[6] = "All Vehicles               < ON >" : lineCaption[6] = "All Vehicles               < OFF >";
			(bonus) ? lineCaption[7] = "Bonus Points             < ON >" : lineCaption[7] = "Bonus Points             < OFF >";

			char textoMaxVel[256];
			sprintf_s(textoMaxVel, "Speed Limit           %6.0fkm/h ", maxVel);

			lineCaption[8] = textoMaxVel;

			CONTROLS::DISABLE_CONTROL_ACTION(2, 27, true);

			DWORD maxTickCount = GetTickCount() + waitTime;
			do {
				CONTROLS::DISABLE_CONTROL_ACTION(2, 27, true);
				draw_menu_line("", lineWidth, 20.5, 16.0, 0.0, 5.0, 0.55, 4, 255, 151, 46, 150, 0, false, true, false, true);
				draw_menu_line(caption, 0.0, 0.0, 28.0, 50.0, 7.5, 0.55, 4, 0, 0, 0, 255, 255, false, true, false, true);
				draw_menu_line(caption, 0.0, 0.0, 28.0, 50.0, 5.0, 0.55, 4, 255, 255, 255, 255, 255, false, true, false, true);
				for(int i = 0; i < lineCount; i++) {
					if(i != activeLineIndexMain) {
						draw_menu_line(lineCaption[i], lineWidth, 9.0, 60.0 + i * 36.0, 0.0, 9.0, 0.36, 0, 255, 255, 255, 80, 255, false, false, false, true);
					}
				}
				draw_menu_line(lineCaption[activeLineIndexMain], lineWidth + 1.0, 11.0, 58.0 + activeLineIndexMain * 36.0, 0.0, 7.0, 0.36, 0, 0, 0, 0, 255, 255, true, false, false, true);
				update_features();
				WAIT(0);
			} while(GetTickCount() < maxTickCount);
			waitTime = 0;

			bool bSelect, bBack, bUp, bDown;
			get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
			if(bSelect || key_pressed(VK_LEFT) || key_pressed(VK_RIGHT)) {
				char texto[24];
				//AUDIO::PLAY_SOUND_FRONTEND(-1, "TRAFFIC_CONTROL_MOVE_CROSSHAIR", "BIG_SCORE_3A_SOUNDS", 1);
				AUDIO::PLAY_SOUND_FRONTEND(-1, "CANCEL", "HUD_LIQUOR_STORE_SOUNDSET", 1);
				switch(activeLineIndexMain) {
					case 0:
						if(usandoW) {
							usandoW = false;
							sprintf_s(texto, "0");
							WritePrivateProfileString(_T("CONFIGURATION"), _T("useWKey"), _T(texto), path);
						} else {
							usandoW = true;
							sprintf_s(texto, "1");
							WritePrivateProfileString(_T("CONFIGURATION"), _T("useWKey"), _T(texto), path);
						}
						break;
					case 1:
						if(efeitoTela) {
							efeitoTela = false;
							sprintf_s(texto, "0");
							WritePrivateProfileString(_T("CONFIGURATION"), _T("screenEffect"), _T(texto), path);
						} else {
							efeitoTela = true;
							sprintf_s(texto, "1");
							WritePrivateProfileString(_T("CONFIGURATION"), _T("screenEffect"), _T(texto), path);
						}
						break;
					case 2:
						if(efeitoSom) {
							efeitoSom = false;
							sprintf_s(texto, "0");
							WritePrivateProfileString(_T("CONFIGURATION"), _T("soundEffect"), _T(texto), path);
						} else {
							efeitoSom = true;
							sprintf_s(texto, "1");
							WritePrivateProfileString(_T("CONFIGURATION"), _T("soundEffect"), _T(texto), path);
						}
						break;
					case 3:
						if(nitroInfinito) {
							nitroInfinito = false;
							sprintf_s(texto, "0");
							WritePrivateProfileString(_T("CONFIGURATION"), _T("infiniteNitro"), _T(texto), path);
						} else {
							nitroInfinito = true;
							sprintf_s(texto, "1");
							WritePrivateProfileString(_T("CONFIGURATION"), _T("infiniteNitro"), _T(texto), path);
						}
						break;
					case 4:
						if(showNumberNitroBar) {
							showNumberNitroBar = false;
							sprintf_s(texto, "0");
							WritePrivateProfileString(_T("CONFIGURATION"), _T("showNitroValue"), _T(texto), path);
						} else {
							showNumberNitroBar = true;
							sprintf_s(texto, "1");
							WritePrivateProfileString(_T("CONFIGURATION"), _T("showNitroValue"), _T(texto), path);
						}
						break;
					case 5:
						if(shakeJoystick) {
							shakeJoystick = false;
							sprintf_s(texto, "0");
							WritePrivateProfileString(_T("CONFIGURATION"), _T("shakeJoystick"), _T(texto), path);
						} else {
							shakeJoystick = true;
							sprintf_s(texto, "1");
							WritePrivateProfileString(_T("CONFIGURATION"), _T("shakeJoystick"), _T(texto), path);
						}
						break;
					case 6:
						if(allVehicles) {
							allVehicles = false;
							sprintf_s(texto, "0");
							WritePrivateProfileString(_T("CONFIGURATION"), _T("allVehicles"), _T(texto), path);
						} else {
							allVehicles = true;
							sprintf_s(texto, "1");
							WritePrivateProfileString(_T("CONFIGURATION"), _T("allVehicles"), _T(texto), path);
						}
						break;
					case 7:
						if (bonus) {
							bonus = false;
							sprintf_s(texto, "0");
							WritePrivateProfileString(_T("CONFIGURATION"), _T("bonus"), _T(texto), path);
						}
						else {
							bonus = true;
							sprintf_s(texto, "1");
							WritePrivateProfileString(_T("CONFIGURATION"), _T("bonus"), _T(texto), path);
						}
						break;
					case 8:
						podeMudarVelocidade = true;						

						novaVelocidade();
						break;
				}
				waitTime = 200;
			} else
			if(bBack || trainer_switch_pressed()) {
				menu_beep(2);
				activeLineIndexMain = 2;
				break;
			} else
			if(bUp) {
				CONTROLS::DISABLE_CONTROL_ACTION(2, 27, true);
				menu_beep(2);
				if(activeLineIndexMain == 0)
					activeLineIndexMain = lineCount;
				activeLineIndexMain--;
				waitTime = 150;
			} else
			if(bDown) {
				menu_beep(2);
				activeLineIndexMain++;
				if(activeLineIndexMain == lineCount)
					activeLineIndexMain = 0;
				waitTime = 150;
			}
		}
	//}
}

void abreMenu() {
	//if(scriptStarted) {
		const float lineWidth = 250.0;
		const int lineCount = 4;

		std::string caption = nomeMod + " v." + versao;
		// "            s"

		DWORD waitTime = 150;
		while(true) {
			string lineCaption[lineCount] = {
				nomeMod,
				"Fun Mode",
				"Configs >>",
				"Credits >>"
			};

			(scriptStarted) ? lineCaption[0] += "        < ON >" : lineCaption[0] += "        < OFF >";
			(modoFun) ? lineCaption[1] += "       < ON >" : lineCaption[1] += "       < OFF >";

			CONTROLS::DISABLE_CONTROL_ACTION(2, 27, true);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 80, true);

			DWORD maxTickCount = GetTickCount() + waitTime;
			do {
				CONTROLS::DISABLE_CONTROL_ACTION(2, 27, true);
				draw_menu_line("", lineWidth, 20.5, 16.0, 0.0, 5.0, 0.55, 4, 0, 0, 0, 100, 0, false, true, false, true);
				draw_menu_line(caption, 0.0, 0.0, 28.0, 65.0, 7.5, 0.55, 4, 0, 0, 0, 255, 255, false, true, false, true);
				draw_menu_line(caption, 0.0, 0.0, 28.0, 65.0, 5.0, 0.55, 4, 255, 255, 255, 255, 255, false, true, false, true);
				for(int i = 0; i < lineCount; i++) {
					if(i != activeLineIndexMain) {
						draw_menu_line(lineCaption[i], lineWidth, 9.0, 60.0 + i * 36.0, 0.0, 9.0, 0.36, 0, 255, 255, 255, 80, 255, false, false, false, true);
					}
				}
				draw_menu_line(lineCaption[activeLineIndexMain], lineWidth + 1.0, 11.0, 58.0 + activeLineIndexMain * 36.0, 0.0, 7.0, 0.36, 0, 255, 255, 255, 255, 255, true, false, false, true);
				update_features();
				WAIT(0);
			} while(GetTickCount() < maxTickCount);
			waitTime = 0;

			bool bSelect, bBack, bUp, bDown;
			get_button_state(&bSelect, &bBack, &bUp, &bDown, NULL, NULL);
			if(bSelect || key_pressed(VK_LEFT) || key_pressed(VK_RIGHT)) {
				CONTROLS::DISABLE_CONTROL_ACTION(2, 27, true);
				//AUDIO::PLAY_SOUND_FRONTEND(-1, "TRAFFIC_CONTROL_MOVE_CROSSHAIR", "BIG_SCORE_3A_SOUNDS", 1);
				AUDIO::PLAY_SOUND_FRONTEND(-1, "CANCEL", "HUD_LIQUOR_STORE_SOUNDSET", 1);
				switch(activeLineIndexMain) {
				case 0:					
					if(scriptStarted) {
						desativaMod();						
					} else {
						bool proximaAtivacaoManualTemp = proximaAtivacaoManual;
						proximaAtivacaoManual = false;
						ativaMod();
						proximaAtivacaoManual = proximaAtivacaoManualTemp;
					}
					break;
				case 1:					
					if(modoFun) {
						modoFun = false;						
					} else {
						modoFun = true;
					}
					break;
				case 2:
					activeLineIndexMain = 0;
					abreMenuConfigs();
					break;
				case 3:
					set_status_text("DEVELOPED BY ~o~PHK", 5500, false, 7, 1.5, 255, 255, 255, 255, 0.5, 0.75);
					char t[255];
					sprintf_s(t, "%s - VERSION: %s - BUILD: %s", nomeMod, versao, build);
					bottomPrint(t, 5500);
					break;
				}
				waitTime = 200;
			} else
			if(bBack || trainer_switch_pressed()) {
				activeLineIndexMain = 0;
				menu_beep(2);
				break;
			} else
			if(bUp) {
				CONTROLS::DISABLE_CONTROL_ACTION(2, 27, true);
				menu_beep(2);
				if(activeLineIndexMain == 0)
					activeLineIndexMain = lineCount;
				activeLineIndexMain--;
				waitTime = 150;
			} else
			if(bDown) {
				menu_beep(2);
				activeLineIndexMain++;
				if(activeLineIndexMain == lineCount)
					activeLineIndexMain = 0;
				waitTime = 150;
			}
		}
	//}
}

void onlineModeError() {	
	if(!mostrouErroOnline) {
		char texto[255];
		sprintf_s(texto, "[~r~ATTENTION~w~]\nYou're in ~g~online mode~w~ and ~y~%s ~w~isn't ~o~supported~w~.", nomeMod);
		notifyAboveMap(texto);
		notifyAboveMap("Please go ~r~offline~w~.\n\nThanks, ~h~PhK.");
		mostrouErroOnline = true;
	}
}

void resetaVariaveis() {
	activeLineIndexMain = 0;
}

void main() {
	resetaVariaveis();

	if(devModeOn) {
		minVelLimite = 0.0;
		maxVelLimite = 539.0;
		sprintf_s(textoLog, "\n[INFO] [%s]: Mod iniciando...\n[INFO] [%s]: Mod iniciado...", dataHoraAtual(), dataHoraAtual());
		salvaLog(textoLog);
	}


	int tempoNoAr = 0;
	int numVoos = 0;
	int timerResetaVoo = 150;
	bool estaNoAr = false;

	while(true) {
		verificaArquivo();
		nitroFunction();

		timerResetaVoo -= 1;

		if (timerResetaVoo == 0 && !estaNoAr) {
			numVoos = 0;
			timerResetaVoo = 150;
		}

		char t[64];
		sprintf_s(t, "NO AR %d - VOOS %d", tempoNoAr, numVoos);
		bottomPrint(t, 100);


		if (ENTITY::IS_ENTITY_IN_AIR(veiculo)) {
			tempoNoAr++;
			if (tempoNoAr == 70) {
				numVoos++;

				char textoar[64];
				string textoVoo = (numVoos < 3) ? textosVoo[numVoos] : textosVoo[2];
				sprintf_s(textoar, "~y~%s", textoVoo);
				set_status_text(textoar, 1000, false, 7, 0.5, 255, 255, 255, 255, 0.5, 0.5);

				tempoNoAr = 0;
			}
			timerResetaVoo = 150;
			estaNoAr = true;
		}
		else {
			tempoNoAr = 0;
			estaNoAr = false;
		}
		
		playerPedId = PLAYER::PLAYER_PED_ID();
		veiculo = PED::GET_VEHICLE_PED_IS_USING(playerPedId);
		veiculoAntigo = PLAYER::GET_PLAYERS_LAST_VEHICLE();
		carroPlayer = PED::GET_VEHICLE_PED_IS_IN(playerPedId, 0);

		if(arquivoEncontrado) {
			/*	KEY MAP
				0xC0 = Y
				0xC1 = X
				0xC3 = ANALOG ESQUERDO -> DIREITA
				0xC4 = ANALOG ESQUERDO -> BAIXO
				0xC5 = ANALOG DIREITO -> DIREITO
				0xC6 = ANALOG DIREITO -> BAIXO
				0xC7 = START
				0xC9 = A
				0xBD = DPAD ESQUERDO
				0xBE = DPAD DIREITO
				0xBF = A
				0xCA = B
				0xCB = X
			*/		

			/*minVelLimite = (devModeOn) ? 0.0 : 100.0;
			maxVelLimite = (devModeOn) ? 539.0 : 300.0;*/

			if(maxNitro < minVelLimite && !devModeOn) {
				maxNitro = 100;
			} else if(maxNitro > 499 && !devModeOn) {
				maxNitro = 500;
			}

			if(maxVel < minVelLimite && !devModeOn) {
				maxVel = minVelLimite;
			} else if(maxVel > maxVelLimite && !devModeOn) {
				maxVel = maxVelLimite;
			}

			if(PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
				float velocidade = ENTITY::GET_ENTITY_SPEED(veiculo);
				float velocidadeKmh = velocidade*kilometerConvert;

				if(velocidadeKmh > calculoVelocidadeAcimaBonus) {
					if(valorNitro < maxNitro - 1) {
						velocidadeAcimaBonus = true;
					}
				} else {
					velocidadeAcimaBonus = false;
				}
			}

			tempoContramao = PLAYER::GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC(PLAYER::PLAYER_ID());
			if(tempoContramao < minTempoContramao) {
				if(valorNitro < maxNitro-1) {					
					estaNaContramao = true;
				}
			} else {								
				estaNaContramao = false;
			}

			if(estaNaContramao && velocidadeAcimaBonus && bonus) {
				nitroPorCiclo = nitroPorCicloSomadoTodosBonus;
			} else if(estaNaContramao && !velocidadeAcimaBonus && bonus) {
				nitroPorCiclo = nitroPorCicloContraMao;
			} else if(!estaNaContramao && velocidadeAcimaBonus && bonus) {
				nitroPorCiclo = nitroPorCicloVelocidade;
			} else {
				nitroPorCiclo = nitroPorCicloPadrao;
			}

			isPlayerOnline = NETWORK::NETWORK_IS_IN_SESSION();			
			if(autoAtivacao && scriptStarted == false) {
				(isPlayerOnline) ? onlineModeError() : ativaMod();
			}

			if(key_pressed(keyActiveMod)) {
				if(!scriptStarted) {
					mostrouErroOnline = false;
					proximaAtivacaoManual = false;
					(isPlayerOnline) ? onlineModeError() : ativaMod();
					if(usandoW) {
						mostraTextoInicial(true);
					} else {
						mostraTextoInicial(false);
					}
				} else {
					desativaMod();
				}
			}
			if(CONTROLS::IS_CONTROL_PRESSED(0, 0xBE) && CONTROLS::IS_CONTROL_PRESSED(0, 0xBF)) {
				if(!scriptStarted) {
					mostrouErroOnline = false;
					proximaAtivacaoManual = false;
					(isPlayerOnline) ? onlineModeError() : ativaMod();
					if(usandoW) {
						mostraTextoInicial(true);
					} else {
						mostraTextoInicial(false);
					}
				} else {
					desativaMod();
				}
			}			

			if(scriptStarted && ENTITY::DOES_ENTITY_EXIST(veiculoAntigo)) {
				if(carroPlayer != veiculoAntigo) {
					valorNitro = maxNitro;
				}
			}

			if(nitroInfinito) {
				valorNitro = maxNitro;
			}

			if(valorNitro > maxNitro) {
				valorNitro = maxNitro;
			}

			if(modoFun) {
				rArquivo = rand() % 255;
				gArquivo = rand() % 255;
				bArquivo = rand() % 255;
			}

			if(key_pressed(keyMenu) && !editandoPosicao /*&& scriptStarted*/) {
				abreMenu();
			}

			if(IsKeyDown(VK_CONTROL) && key_pressed(VK_ADD) && scriptStarted && devModeOn) {
				valorNitro = maxNitro;
				char texto[255];
				sprintf_s(texto, "[%s] Dev Access Key\nnitroValue = %1.2lf", nomeMod, maxNitro);
				mostraTextoEsquerda(texto);
			}

			if(IsKeyDown(VK_CONTROL) && key_pressed(VK_MULTIPLY) && scriptStarted && devModeOn) {
				maxNitro += 50.0f;
				char texto[255];
				sprintf_s(texto, "[%s] Dev Access Key\nmaxNitro = %1.2lf", nomeMod, maxNitro);
				mostraTextoEsquerda(texto);
			}

			if(IsKeyDown(VK_CONTROL) && key_pressed(VK_DIVIDE) && scriptStarted && devModeOn) {
				maxNitro -= 50.0f;
				char texto[255];
				sprintf_s(texto, "[%s] Dev Access Key\nmaxNitro = %1.2lf", nomeMod, maxNitro);
				mostraTextoEsquerda(texto);
			}

			if(key_pressed(keyFunMod) && scriptStarted) {
				if(modoFun == false) {
					modoFun = true;
					nitroPorCiclo = 1;
					nitroRemovido = 2;
					valorTimerNitroMax = 16;
					char t[64];
					sprintf_s(t, "[~g~%s~w~] ~y~F~g~u~b~n ~r~M~b~o~y~d~g~e ~w~activated.", nomeMod);
					bottomPrint(t, 4500);
				} else {
					modoFun = false;
					nitroPorCiclo = nitroPorCicloPadrao;
					nitroRemovido = nitroRemovidoPadrao;
					valorTimerNitroMax = valorTimerNitroMaxPadrao;
					char t[64];
					sprintf_s(t, "[~g~%s~w~] ~y~F~g~u~b~n ~r~M~b~o~y~d~g~e ~w~deactivated.", nomeMod);
					bottomPrint(t, 4500);
				}
			}
			
			char text[256];			
			if(key_pressed(keySavePosition)) {
				if(!editandoPosicao) {
					editandoPosicao = true;
					//~y~EDIT MODE ACTIVATED~w~! PRESS ~g~%s ~w~TO ~r~SAVE ~w~THE POSITION AND DISABLE THE EDIT MODE!
					sprintf_s(text, "EDIT MODE ACTIVATED! PRESS %s TO SAVE THE POSITION", teclaPosicao);

					//set_status_text(text, 5000, false, 4);
					StartLoadingMessage(text, 2);
				} else {
					editandoPosicao = false;

					UI::_0x10D373323E5B9C0D();

					char posicaoX[24];
					sprintf_s(posicaoX, "%f", posX);
					WritePrivateProfileString(_T("CONFIGURATION"), _T("posX"), _T(posicaoX), path);

					char posicaoY[24];
					sprintf_s(posicaoY, "%f", posY);
					WritePrivateProfileString(_T("CONFIGURATION"), _T("posY"), _T(posicaoY), path);

					DWORD time = GetTickCount() + 1000;
					while(GetTickCount() < time) {
						sprintf_s(text, "~g~SAVED~w~!\nX: ~r~%3.2lf ~w~| Y: ~r~%3.2lf", posX, posY);
						notifyAboveMap(text);
						WAIT(0);
					}
				}
			}

			if(editandoPosicao && scriptStarted) {				
				char text[256];
				sprintf_s(text, "~g~NPAD8 ~w~= ~g~UP~w~\n~r~NPAD5 ~w~= ~r~DWN~w~\n~g~NPAD4 ~w~= ~g~LFT~w~\n~r~NPAD5 ~w~= ~r~RGT", nomeMod);
				mostraTextoEsquerda(text);

				// NUM PAD - - -50X
				if(IsKeyDown(VK_NUMPAD8)) {
					posX -= baseCalculo;
				}
				// NUM PAD + - +50X
				if(IsKeyDown(VK_NUMPAD5)) {
					posX += baseCalculo;
				}				
				// NUM PAD / - +50Y
				if(IsKeyDown(VK_NUMPAD6)) {
					posY += baseCalculo;
				}
				// NUM PAD * - -50Y
				if(IsKeyDown(VK_NUMPAD4)) {
					posY -= baseCalculo;
				}				
			}			
			update_features();
		} else {
			keyActiveMod = VK_F5;
			DWORD time = GetTickCount() + 1000;
			while (GetTickCount() < time) {
				char text[256];
				sprintf_s(text, "-= File %s not found. Using F5 as default key. =-", arquivo);
				set_status_text(text);
				update_features();
				WAIT(0);
			}
			//scriptStarted = false;
		}
	}
}

void ScriptMain() {
	srand(GetTickCount());

	FILE *file;

	file = fopen(arquivoDev, "r");
	if(file != NULL) 
		devModeOn = true;

	if(devModeOn) {
		file = fopen(arquivoLog, "w");
		verificaArquivo();

		char versaoWindows[255], buildWindows[255], osWindows[255];

		HKEY key;
		if(RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion"), &key) == ERROR_SUCCESS) {
			char value[MAX_PATH], text[255];
			DWORD value_length = MAX_PATH;

			sprintf_s(text, "");

			RegQueryValueEx(key, TEXT("CurrentVersion"), NULL, NULL, (LPBYTE)&value, &value_length);

			for(int i = 0; i < value_length; i++) {
				sprintf_s(text, "%s%c", text, value[i]);
			}

			sprintf_s(versaoWindows, "%s", text);

			RegCloseKey(key);
		}

		if(RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion"), &key) == ERROR_SUCCESS) {
			char value[MAX_PATH], text[255];
			DWORD value_length = MAX_PATH;

			sprintf_s(text, "");

			RegQueryValueEx(key, TEXT("CurrentBuild"), NULL, NULL, (LPBYTE)&value, &value_length);

			for(int i = 0; i < value_length; i++) {
				sprintf_s(text, "%s%c", text, value[i]);
			}

			sprintf_s(buildWindows, "%s", text);

			RegCloseKey(key);
		}

		if(RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion"), &key) == ERROR_SUCCESS) {
			char value[MAX_PATH], text[255];
			DWORD value_length = MAX_PATH;

			sprintf_s(text, "");

			RegQueryValueEx(key, TEXT("ProductName"), NULL, NULL, (LPBYTE)&value, &value_length);

			for(int i = 0; i < value_length; i++) {
				sprintf_s(text, "%s%c", text, value[i]);
			}

			sprintf_s(osWindows, "%s", text);

			RegCloseKey(key);
		}

		TCHAR NPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, NPath);

		sprintf_s(textoLog, "-- THIS FILE WAS GENERATED BECAUSE OF nitroMod.dev\n-- Send the log from here\n(C) PhK %s %s %s %s", nomeMod, versao, build, NPath);
		sprintf_s(textoLog, "%s\n%s %s %s (%s)", textoLog, osWindows, pegaWindowsVersao(buildWindows), versaoWindows, buildWindows);
		sprintf_s(textoLog, "%s\n\n[INFO] [%s]: Inicializando suporte...", textoLog, dataHoraAtual());
		sprintf_s(textoLog, "%s\n[INFO] [%s]: arquivo => '%s'", textoLog, dataHoraAtual(), arquivo);
		sprintf_s(textoLog, "%s\n[INFO] [%s]: path => '%s'", textoLog, dataHoraAtual(), path);
		sprintf_s(textoLog, "%s\n[INFO] [%s]: arquivoDev => '%s'", textoLog, dataHoraAtual(), arquivoDev);
		sprintf_s(textoLog, "%s\n[INFO] [%s]: arquivoLog => '%s'", textoLog, dataHoraAtual(), arquivoLog);
		file = fopen(arquivo, "r");
		if(file != NULL) {
			sprintf_s(textoLog, "%s\n[+] Configurações atuais carregadas do arquivo:", textoLog);
			sprintf_s(textoLog, "%s\n[INFO] [%s]: screenEffect => '%d'", textoLog, dataHoraAtual(), efeitoTela);
			sprintf_s(textoLog, "%s\n[INFO] [%s]: soundEffect => '%d'", textoLog, dataHoraAtual(), efeitoSom);
			sprintf_s(textoLog, "%s\n[INFO] [%s]: useWKey => '%d'", textoLog, dataHoraAtual(), usandoW);
			sprintf_s(textoLog, "%s\n[INFO] [%s]: infiniteNitro => '%d'", textoLog, dataHoraAtual(), nitroInfinito);
			sprintf_s(textoLog, "%s\n[INFO] [%s]: maxVel => '%3.2lf'", textoLog, dataHoraAtual(), maxVel);
			sprintf_s(textoLog, "%s\n[INFO] [%s]: allVehicles => '%d'", textoLog, dataHoraAtual(), allVehicles);
			sprintf_s(textoLog, "%s\n[INFO] [%s]: posX => '%3.1lf'", textoLog, dataHoraAtual(), posX);
			sprintf_s(textoLog, "%s\n[INFO] [%s]: posY => '%3.1lf'", textoLog, dataHoraAtual(), posY);
			sprintf_s(textoLog, "%s\n[INFO] [%s]: barRed => '%d'", textoLog, dataHoraAtual(), rArquivo);
			sprintf_s(textoLog, "%s\n[INFO] [%s]: barGreen => '%d'", textoLog, dataHoraAtual(), gArquivo);
			sprintf_s(textoLog, "%s\n[INFO] [%s]: barBlue => '%d'", textoLog, dataHoraAtual(), bArquivo);
			sprintf_s(textoLog, "%s\n[INFO] [%s]: autoActive => '%d'", textoLog, dataHoraAtual(), autoAtivacao);
			sprintf_s(textoLog, "%s\n[INFO] [%s]: showNitroValue => '%d'", textoLog, dataHoraAtual(), showNumberNitroBar);
			sprintf_s(textoLog, "%s\n[INFO] [%s]: shakeJoystick => '%d'", textoLog, dataHoraAtual(), shakeJoystick);
			sprintf_s(textoLog, "%s\n[INFO] [%s]: flameMultiplier => '%3.1lf'", textoLog, dataHoraAtual(), flameMultiplier);
			sprintf_s(textoLog, "%s\n[INFO] [%s]: bonus => '%d'", textoLog, dataHoraAtual(), bonus);
		} else {
			sprintf_s(textoLog, "%s\n[!!!!] [%s]: %s não encontrado (%s not found)", textoLog, dataHoraAtual(), arquivo, arquivo);
		}
		sprintf_s(textoLog, "%s\n[+] Valores de variáveis:", textoLog);
		sprintf_s(textoLog, "%s\n[INFO] [%s]: maxNitro => '%3.2lf'", textoLog, dataHoraAtual(), maxNitro);
		sprintf_s(textoLog, "%s\n[INFO] [%s]: nitroPorCiclo => '%3.2lf'", textoLog, dataHoraAtual(), nitroPorCiclo);
		sprintf_s(textoLog, "%s\n[INFO] [%s]: nitroPorCicloPadrao => '%3.2lf'", textoLog, dataHoraAtual(), nitroPorCicloPadrao);
		sprintf_s(textoLog, "%s\n[INFO] [%s]: nitroPorCicloContraMao => '%3.2lf'", textoLog, dataHoraAtual(), nitroPorCicloContraMao);
		sprintf_s(textoLog, "%s\n[INFO] [%s]: nitroPorCicloVelocidade => '%3.2lf'", textoLog, dataHoraAtual(), nitroPorCicloVelocidade);
		sprintf_s(textoLog, "%s\n[INFO] [%s]: valorTimerNitroMax => '%i'", textoLog, dataHoraAtual(), valorTimerNitroMax);
		sprintf_s(textoLog, "%s\n[INFO] [%s]: minTempoContramao => '%i'", textoLog, dataHoraAtual(), minTempoContramao);
		sprintf_s(textoLog, "%s\n[INFO] [%s]: minVelLimite => '%3.1lf'", textoLog, dataHoraAtual(), minVelLimite);
		sprintf_s(textoLog, "%s\n[INFO] [%s]: maxVelLimite => '%3.1lf'", textoLog, dataHoraAtual(), maxVelLimite);

		salvaLog(textoLog);
	}

	main();
}