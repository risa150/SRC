@rem 2.1��2.2�ɃA�b�v�O���[�h���邽�߂̃o�b�`�t�@�C��������Ă݂��@[2015/7/28 �i�J]
@echo off
echo STM32F4 Discovery 2�w��� ver.Taiki �h���C�o��2.2�Ή�������o�b�`�t�@�C��
pause
COPY /Y can.cpp ..\layer_driver\base\
COPY /Y can.hpp ..\layer_driver\base\
COPY /Y pin.cpp ..\layer_driver\board\
COPY /Y pin.cpp ..\layer_driver\board\
COPY /Y can_encoder.cpp ..\layer_driver\circuit\
COPY /Y can_encoder.hpp ..\layer_driver\circuit\
echo 2.2 upgraded >> ..\log.txt
echo �K�v�ȃt�@�C���̃R�s�[���������܂����B
echo .
echo /layer_driver/base��can.hpp��can.cpp���ǉ����ꂽ�̂�
echo �������v���W�F�N�g�ɒǉ����Ă��������B
echo �������Ȃ��Ƃ��Ԃ�R���p�C���G���[�ɂȂ��B
echo .
pause