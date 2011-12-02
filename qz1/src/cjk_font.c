/*
*Derived from the cpp version. 
*kar1125
*/

#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include "cjk_font.h"

static FT_Library 	m_library;   // 字库
static FT_Face		m_face;      // 字体
static CvScalar		m_fontSize;
static float 		m_fontDiaphaneity;

static void putWChar(IplImage *img, wchar_t wc, CvPoint *pos, CvScalar color);


int initFont(const char *fontfile)
{
	if(FT_Init_FreeType(&m_library)){
		fprintf(stderr,"FreeType init failed.\n");
		return 1;
	}

	if(FT_New_Face(m_library, fontfile, 0, &m_face)){
		fprintf(stderr,"Load fontfile %s failed.\n",fontfile);
		return 1;
	}

	restoreFont();
	return 0;
}

void setFont(CvScalar *size,float diaphaneity)
{
	if(size)
	{
		m_fontSize.val[0] = fabs(size->val[0]);
		m_fontSize.val[1] = fabs(size->val[1]);
		m_fontSize.val[2] = fabs(size->val[2]);
		m_fontSize.val[3] = fabs(size->val[3]);
	}
	if(diaphaneity)
	{
		m_fontDiaphaneity = diaphaneity;
	}
	FT_Set_Pixel_Sizes(m_face, (int)m_fontSize.val[0], 0);
}



void restoreFont()
{
	m_fontSize.val[0] = 20;      // 字体大小
	m_fontSize.val[1] = 0.5;   // 空白字符大小比例
	m_fontSize.val[2] = 0.1;   // 间隔大小比例
	m_fontSize.val[3] = 0;      // 旋转角度(不支持)


	m_fontDiaphaneity = 1.0;   // 色彩比例(可产生透明效果)

	// 设置字符大小
	FT_Set_Pixel_Sizes(m_face, (int)m_fontSize.val[0], 0);
}


int putText(IplImage *img, const char *text, CvPoint pos)
{
	return putColorText(img, text, pos, CV_RGB(2,255,0));
}

int putColorText(IplImage *img, const char *text, CvPoint pos, CvScalar color)
{
	if(img == NULL) return -1;
	if(text == NULL) return -1;

	int i;
	CvPoint npos;
	npos.x=pos.x;
	npos.y=pos.y;

	setlocale(LC_CTYPE, "zh_CN.UTF-8");
	for(i = 0; text[i] != '\0'; i++){
		wchar_t wc = text[i];
		// 解析双字节符号
		//		printf("%d->%c[%d]\n",i,text[i],isascii(wc));
		int r;
		if(!isascii(wc)){
			r=mbtowc(&wc, &text[i], 3);
			i+=2;
		}
		//printf("%d\n",r);
		// 输出当前的字符
		putWChar(img, wc, &npos, color);
	}
	return 0;
}

static void putWChar(IplImage *img, wchar_t wc, CvPoint *pos, CvScalar color)
{
	//	printf("DBG:%s\n",wc);
	FT_UInt glyph_index = FT_Get_Char_Index(m_face, wc);
	FT_Load_Glyph(m_face, glyph_index, FT_LOAD_DEFAULT);
	FT_Render_Glyph(m_face->glyph, FT_RENDER_MODE_MONO);

	FT_GlyphSlot slot = m_face->glyph;

	// 行列数

	int rows = slot->bitmap.rows;
	int cols = slot->bitmap.width;

	int i,j,k;

	for(i = 0; i < rows; ++i)
	{
		for(j = 0; j < cols; ++j)
		{
			int off  = ((img->origin==0)? i: (rows-1-i))
				* slot->bitmap.pitch + j/8;

			if(slot->bitmap.buffer[off] & (0xC0 >> (j%8)))
			{
				int r = (img->origin==0)? pos->y - (rows-1-i): pos->y + i;;
				int c = pos->x + j;

				if(r >= 0 && r < img->height
						&& c >= 0 && c < img->width)
				{
					CvScalar scalar = cvGet2D(img, r, c);

					// 进行色彩融合

					float p = m_fontDiaphaneity;
					for(k = 0; k < 4; ++k)
					{
						scalar.val[k] = scalar.val[k]*(1-p) + color.val[k]*p;
					}

					cvSet2D(img, r, c, scalar);
				}
			}
		} // end for
	} // end for

	// 修改下一个字的输出位置

	double space = m_fontSize.val[0]*m_fontSize.val[1];
	double sep   = m_fontSize.val[0]*m_fontSize.val[2];

	pos->x += (int)((cols? cols: space) + sep);	
}

void disposeFont()
{
	    FT_Done_Face(m_face);
		    FT_Done_FreeType(m_library);
}

