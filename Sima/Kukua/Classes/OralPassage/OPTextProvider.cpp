#include "OPTextProvider.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <vector>
#include <string>

#include "../Utils/StringUtility.h"

#include "../Utils/Data/DataProvider.h"


USING_NS_CC;

using namespace cocostudio::timeline;
using namespace std;



OPTextProvider::OPTextProvider()
{
    string currentPhoneme = DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme();
    CCLOG("currentPhoneme = %s", currentPhoneme.c_str());
    currentPhonemeNum = 1;
    if (currentPhoneme == "extraOralPassagebubble5_ep7")       currentPhonemeNum = 1;
    else if (currentPhoneme == "extraOralPassagebubble10_ep7") currentPhonemeNum = 2;
    else if (currentPhoneme == "extraOralPassagebubble15_ep7") currentPhonemeNum = 3;
    else if (currentPhoneme == "extraOralPassagebubble20_ep7") currentPhonemeNum = 4;
    else if (currentPhoneme == "extraOralPassagebubble5_ep8")  currentPhonemeNum = 5;
    else if (currentPhoneme == "extraOralPassagebubble10_ep8") currentPhonemeNum = 6;
    else if (currentPhoneme == "extraOralPassagebubble15_ep8") currentPhonemeNum = 7;
    else if (currentPhoneme == "extraOralPassagebubble20_ep8") currentPhonemeNum = 8;
    else if (currentPhoneme == "extraOralPassagebubble5_ep9")  currentPhonemeNum = 9;
    else if (currentPhoneme == "extraOralPassagebubble10_ep9") currentPhonemeNum = 10;
    else if (currentPhoneme == "extraOralPassagebubble15_ep9") currentPhonemeNum = 11;
    else if (currentPhoneme == "extraOralPassagebubble20_ep9") currentPhonemeNum = 12;
    CCLOG(">> currentPhonemeNum = %d", currentPhonemeNum);
}


OPTextProvider::~OPTextProvider() {
    
}


string OPTextProvider::getAnswer1Correct(int num) {
    string answer = "";
    
    
    if (currentPhonemeNum == 1) {
    
        if (num == 1) answer ="عادل";
        else if (num == 2) answer ="كتاب جديد";
        else if (num == 3) answer ="يوجد في الكتاب دروس مفيدة";
        else if (num == 4) answer ="نظيف وجميل";
        else if (num == 5) answer ="عادل يحب كتابه";
        
    } else if (currentPhonemeNum == 2) {
        
        if (num == 1) answer ="يوجد في القرية منازل قليلة";
        else if (num == 2) answer ="شوارع ضيقة";
        else if (num == 3) answer ="يسكنها الفلاحون";
        else if (num == 4) answer ="يوجد حولها حقول ومزارع كبيرة";
        else if (num == 5) answer ="أهل القرية لطفاء";
        
    } else if (currentPhonemeNum == 3) {
        
        if (num == 1) answer ="اللص";
        else if (num == 2) answer ="دخل الى المنزل ليسرق";
        else if (num == 3) answer ="ليلا";
        else if (num == 4) answer ="أخذ ينبح";
        else if (num == 5) answer ="هرب خائف مرعوب";
        
    } else if (currentPhonemeNum == 4) {
        
        if (num == 1) answer ="يحتاج الى غذاء جيد";
        else if (num == 2) answer ="ليحافظ على صحته";
        else if (num == 3) answer ="يزوده بالقوة";
        else if (num == 4) answer ="يتكون من لحم وخضار ودهن وبيض وفاكهة";
        else if (num == 5) answer ="ضعيفا";
        
    } else if (currentPhonemeNum == 5) {
        
        if (num == 1) answer ="تعيش النحلة في جماعات متعاونة";
        else if (num == 2) answer ="للنحلة أربعة اجنحة";
        else if (num == 3) answer ="من زهرة الى زهرة";
        else if (num == 4) answer ="عسل";
        else if (num == 5) answer ="يشفي من الامراض";
        
    } else if (currentPhonemeNum == 6) {
        
        if (num == 1) answer ="في بيت جدي";
        else if (num == 2) answer ="على الطريق الزراعي";
        else if (num == 3) answer ="اقطف الزهور";
        else if (num == 4) answer =" العب مع الحيوانات";
        else if (num == 5) answer ="الحلوى ";
        
    } else if (currentPhonemeNum == 7) {
        
        if (num == 1) answer ="كرة جميلة";
        else if (num == 2) answer ="يضربها بقدمه";
        else if (num == 3) answer ="مع اخوته واصدقاءه";
        else if (num == 4) answer ="في الملعب الكبير";
        else if (num == 5) answer ="يريد ان يصبح لاعبا مشهورا";
        
    } else if (currentPhonemeNum == 8) {
        
        if (num == 1) answer ="نشيط";
        else if (num == 2) answer ="بالماء والصابون";
        else if (num == 3) answer ="يساعده في عمله";
        else if (num == 4) answer ="يوصلها الى البيت";
        else if (num == 5) answer ="يساعدها في تحضير العشاء";
        
    } else if (currentPhonemeNum == 9) {
        
        if (num == 1) answer ="في الصف الاول";
        else if (num == 2) answer ="شاهد الطيور";
        else if (num == 3) answer ="كسر يده";
        else if (num == 4) answer ="الى المستشفى";
        else if (num == 5) answer ="الطبيب";
        
    } else if (currentPhonemeNum == 10) {
        
        if (num == 1) answer ="ذهب طارق مع ابيه في رحلة لصيد السمك";
        else if (num == 2) answer ="أدوات الصيد";
        else if (num == 3) answer ="سترة النجاة";
        else if (num == 4) answer ="الكثير من الأسماك ";
        else if (num == 5) answer ="عادوا فرحين";
        
    } else if (currentPhonemeNum == 11) {
        
        if (num == 1) answer ="ذهبوا الى حديقة الحيوان";
        else if (num == 2) answer ="الاسد";
        else if (num == 3) answer ="تاكل الموز";
        else if (num == 4) answer ="البرسيم";
        else if (num == 5) answer ="الاسماك";
        
    } else if (currentPhonemeNum == 12) {
        
        if (num == 1) answer = "ريما تحب الحيوانات";
        else if (num == 2) answer = "لون الكلب ابيض";
        else if (num == 3) answer = "حزنت ريما كثيرا";
        else if (num == 4) answer = "طلبت من والدها ان يساعدها";
        else if (num == 5) answer = "وجده في الحديقة الكبيرة جانب البيت";
    }
        
    return answer;
}


string OPTextProvider::getAnswer2(int num) {
    string answer = "";
    
    if (currentPhonemeNum == 1) {
        
        if (num == 1) answer ="وائل";
        else if (num == 2) answer ="كتاب قديم";
        else if (num == 3) answer =" يوجد في الكتاب آسماء كثيرة";
        else if (num == 4) answer ="مهذب وشاطر";
        else if (num == 5) answer ="عادل يحب حقيبته";
        
    } else if (currentPhonemeNum == 2) {
        
        if (num == 1) answer ="يوجد في القرية وحوش كبيرة";
        else if (num == 2) answer ="شوارع عريضة";
        else if (num == 3) answer ="يسكنها العمال";
        else if (num == 4) answer ="يوجد حولها مطاعم وفنادق كبيرة";
        else if (num == 5) answer ="أهل القرية أغنياء ";
        
    } else if (currentPhonemeNum == 3) {
        
        if (num == 1) answer ="الكلب";
        else if (num == 2) answer ="دخل الى المنزل ليلعب";
        else if (num == 3) answer ="صباحا";
        else if (num == 4) answer ="أخذ يرقص";
        else if (num == 5) answer ="هرب سعيد مسرور";
        
    } else if (currentPhonemeNum == 4) {
        
        if (num == 1) answer ="يحتاج الى ملابس جديدة";
        else if (num == 2) answer ="ليحافظ على العابه";
        else if (num == 3) answer ="يزوده بالمال";
        else if (num == 4) answer ="يتكون من لحم وجلود ودهن وبيض وفاكهة";
        else if (num == 5) answer ="قويا";
        
    } else if (currentPhonemeNum == 5) {
        
        if (num == 1) answer ="تعيش النحلة في بيوت زجاجية";
        else if (num == 2) answer ="للنحلة ثلاث اجنحة";
        else if (num == 3) answer ="من شباك الى شباك";
        else if (num == 4) answer ="زيتون";
        else if (num == 5) answer ="يساعد على النوم";
        
    } else if (currentPhonemeNum == 6) {
        
        if (num == 1) answer ="في بيت خالي";
        else if (num == 2) answer ="على الطريق الصحراوي";
        else if (num == 3) answer ="اقطف الخضار";
        else if (num == 4) answer ="العب مع الفراشات";
        else if (num == 5) answer ="البيتزا ";
        
    } else if (currentPhonemeNum == 7) {
        
        if (num == 1) answer ="كتاب جديد";
        else if (num == 2) answer ="يضربها بيده";
        else if (num == 3) answer ="مع جده وجدته";
        else if (num == 4) answer ="في المسرح الكبير";
        else if (num == 5) answer ="يريد ان يصبح طبيبا مشهورا";
        
    } else if (currentPhonemeNum == 8) {
        
        if (num == 1) answer ="كسول";
        else if (num == 2) answer ="بالزيت والصابون";
        else if (num == 3) answer ="يساعده في اكله";
        else if (num == 4) answer ="يوصلها الى المدرسة";
        else if (num == 5) answer ="يساعدها في غسيل الاطباق";
        
    } else if (currentPhonemeNum == 9) {
        
        if (num == 1) answer ="في الصف الرابع";
        else if (num == 2) answer ="شاهد الكلاب";
        else if (num == 3) answer ="كسر إصبعه ";
        else if (num == 4) answer ="الى المدرسة";
        else if (num == 5) answer ="المهندس";
        
    } else if (currentPhonemeNum == 10) {
        
        if (num == 1) answer ="ذهب طارق مع وابيه الى حفلة موسيقية";
        else if (num == 2) answer ="أدوات الحفر";
        else if (num == 3) answer ="مفتاح السيارة";
        else if (num == 4) answer ="الكثير من العصافير";
        else if (num == 5) answer ="عادوا غاضبين";
        
    } else if (currentPhonemeNum == 11) {
        
        if (num == 1) answer ="ذهبوا الى الحديقة العامة";
        else if (num == 2) answer ="النمر";
        else if (num == 3) answer ="تاكل التفاح";
        else if (num == 4) answer ="الحشيش";
        else if (num == 5) answer ="الضفادع";
        
    } else if (currentPhonemeNum == 12) {
        
        if (num == 1) answer ="ريما تحب الحلويات";
        else if (num == 2) answer ="لون الكلب بني";
        else if (num == 3) answer ="فرحت ريما كثيرا";
        else if (num == 4) answer ="طلبت من صديقها ان يساعدها";
        else if (num == 5) answer ="وجده في الحديقة الصغيرة جانب البيت";
    }
    
    return answer;
}

string OPTextProvider::getAnswer3(int num) {
    string answer = "";
    
    if (currentPhonemeNum == 1) {
        
        if (num == 1) answer ="كامل";
        else if (num == 2) answer ="كتاب ممزق";
        else if (num == 3) answer ="يوجد في الكتاب أفلام جميلة";
        else if (num == 4) answer ="وسخ وممزق";
        else if (num == 5) answer ="عادل يحب حذاءه";
        
    } else if (currentPhonemeNum == 2) {
        
        if (num == 1) answer ="يوجد في القرية اسماك ملونة";
        else if (num == 2) answer ="شوارع مضيئة";
        else if (num == 3) answer ="يسكنها التجار";
        else if (num == 4) answer ="يوجد حولها معامل ومصانع كبيرة";
        else if (num == 5) answer ="أهل القرية بخلاء";
        
    } else if (currentPhonemeNum == 3) {
        
        if (num == 1) answer ="الحارس";
        else if (num == 2) answer ="دخل الى المنزل ليأكل ";
        else if (num == 3) answer ="ظهرا";
        else if (num == 4) answer ="أخذ يركض";
        else if (num == 5) answer ="هرب حزين باكي";
        
    } else if (currentPhonemeNum == 4) {
        
        if (num == 1) answer ="يحتاج الى حلوى لذيذة";
        else if (num == 2) answer ="ليحافظ على ثيابه";
        else if (num == 3) answer ="يزوده بالاحلام";
        else if (num == 4) answer ="يتكون من لحم وخضار ودهن وبيض ومعادن";
        else if (num == 5) answer ="طويلا";
        
    } else if (currentPhonemeNum == 5) {
        
        if (num == 1) answer ="تعيش النحلة في احواض مائية";
        else if (num == 2) answer ="للنحلة سبعة اجنحة";
        else if (num == 3) answer ="من شجرة الى شجرة";
        else if (num == 4) answer ="شاي";
        else if (num == 5) answer ="يقوي العضلات";
        
    } else if (currentPhonemeNum == 6) {
        
        if (num == 1) answer ="في بيت عمي";
        else if (num == 2) answer ="على الطريق الجبلي";
        else if (num == 3) answer ="اقطف الفاكهة";
        else if (num == 4) answer ="العب مع الأسماك ";
        else if (num == 5) answer ="المثلجات";
        
    } else if (currentPhonemeNum == 7) {
        
        if (num == 1) answer ="صندوق صغير";
        else if (num == 2) answer ="يضربها برأسه";
        else if (num == 3) answer ="مع أمه وابيه";
        else if (num == 4) answer ="في المصنع الكبير";
        else if (num == 5) answer ="يريد ان يصبح رساما مشهورا";
        
    } else if (currentPhonemeNum == 8) {
        
        if (num == 1) answer ="مشاغب";
        else if (num == 2) answer ="بالحليب والصابون";
        else if (num == 3) answer ="يساعده في نومه";
        else if (num == 4) answer ="يوصلها الى الملعب";
        else if (num == 5) answer ="يساعدها في كُوي الملابس";
        
    } else if (currentPhonemeNum == 9) {
        
        if (num == 1) answer ="في الصف العاشر";
        else if (num == 2) answer ="شاهد القطط";
        else if (num == 3) answer ="كسر قدمه";
        else if (num == 4) answer ="الى الملعب";
        else if (num == 5) answer ="الفلاح";
        
    } else if (currentPhonemeNum == 10) {
        
        if (num == 1) answer ="ذهب طارق مع ابيه الى زيارة عائلية";
        else if (num == 2) answer ="أدوات الطبخ";
        else if (num == 3) answer ="ملعقة الطعام";
        else if (num == 4) answer ="الكثير من الغزلان";
        else if (num == 5) answer ="عادوا حزينين";
        
    } else if (currentPhonemeNum == 11) {
        
        if (num == 1) answer ="ذهبوا الى الغابة";
        else if (num == 2) answer ="الفيل";
        else if (num == 3) answer ="تاكل العنب";
        else if (num == 4) answer ="اللحم";
        else if (num == 5) answer ="الديدان";
        
    } else if (currentPhonemeNum == 12) {
        
        if (num == 1) answer ="ريما تحب الحشرات";
        else if (num == 2) answer ="لون الكلب اسود";
        else if (num == 3) answer ="جاعت ريما كثيرا";
        else if (num == 4) answer ="طلبت من اخيها ان يساعدها";
        else if (num == 5) answer ="وجده في الحديقة الكبيرة بجانب النهر";
    }
    
    return answer;
}

string OPTextProvider::getQuestion(int num) {
    string question = "";
    
    if (currentPhonemeNum == 1) {
        
        if (num == 1) question ="من هو صاحب الكتاب؟";
        else if (num == 2) question ="كيف هو الكتاب؟";
        else if (num == 3) question ="ماذا يوجد في الكتاب؟";
        else if (num == 4) question ="كيف هو غلاف الكتاب؟";
        else if (num == 5) question ="ماذا يحب عادل؟";
        
    } else if (currentPhonemeNum == 2) {
        
        if (num == 1) question ="ماذا يوجد في القرية؟";
        else if (num == 2) question ="كيف هي شوارع القرية؟";
        else if (num == 3) question ="من يسكن القرية؟";
        else if (num == 4) question ="ماذا يوجد حول القرية؟";
        else if (num == 5) question ="كيف هم أهل القرية؟";
        
    } else if (currentPhonemeNum == 3) {
        
        if (num == 1) question ="من الذي دخل المنزل؟";
        else if (num == 2) question ="لماذا دخل اللص الى المنزل؟";
        else if (num == 3) question ="متى دخل اللص الى المنزل؟";
        else if (num == 4) question ="ماذا فعل الكلب؟";
        else if (num == 5) question ="كيف هرب اللص؟";
        
    } else if (currentPhonemeNum == 4) {
        
        if (num == 1) question ="الى ماذا يحتاج الانسان؟";
        else if (num == 2) question ="لماذا يحتاج الانسان الى غذاء جيد؟";
        else if (num == 3) question ="ماذا يعمل الغذاء الجيد للإنسان؟";
        else if (num == 4) question ="من ماذا يتكون غذاء الانسان؟";
        else if (num == 5) question ="من لا يتناول الغذاء الجيد سيُصبِح جسمه؟";
        
    } else if (currentPhonemeNum == 5) {
        
        if (num == 1) question ="أين تعيش النحلة؟";
        else if (num == 2) question ="كم جناح النحلة؟";
        else if (num == 3) question ="أين تتنقل النحلة؟";
        else if (num == 4) question ="ماذا تخرج لنا النحلة؟";
        else if (num == 5) question ="ماذا يفيد العسل؟";
        
    } else if (currentPhonemeNum == 6) {
        
        if (num == 1) question ="أين قضيت عطلة الصيف؟";
        else if (num == 2) question ="أين كنت أتمشى؟";
        else if (num == 3) question ="ماذا كنت اقطف؟";
        else if (num == 4) question ="مع من كنت العب؟";
        else if (num == 5) question ="ماذا صنعت لي جدتي؟ ";
        
    } else if (currentPhonemeNum == 7) {
        
        if (num == 1) question ="ماذا يوجد عند كريم؟";
        else if (num == 2) question ="بماذا يضرب كريم الكرة؟";
        else if (num == 3) question ="مع من يلعب كريم؟";
        else if (num == 4) question ="أين يلعب كريم بالكرة؟";
        else if (num == 5) question ="ماذا يريد ان يصبح كريم عندما يكبر؟ ";
        
    } else if (currentPhonemeNum == 8) {
        
        if (num == 1) question ="باسم ولد؟";
        else if (num == 2) question ="بماذا يغسل كريم وجهه كل يوم؟";
        else if (num == 3) question ="بماذا يساعد كريم والده؟";
        else if (num == 4) question ="الى أين يوصل كريم الخضار؟";
        else if (num == 5) question ="بماذا يساعد كريم والدته؟";
        
    } else if (currentPhonemeNum == 9) {
        
        if (num == 1) question ="في اي صف طارق؟";
        else if (num == 2) question ="ماذا شاهد طارق في حديقة منزلهم؟";
        else if (num == 3) question ="ماذا حدث لطارق عندما سقط على الارض؟";
        else if (num == 4) question ="الى أين حمله والده؟";
        else if (num == 5) question ="من عالج يد طارق؟";
        
    } else if (currentPhonemeNum == 10) {
        
        if (num == 1) question ="الى أين ذهب خالد مع ابيه؟";
        else if (num == 2) question ="ماهي الأدوات التي أحضروها معهم؟";
        else if (num == 3) question ="مالذي لم ينسوه؟";
        else if (num == 4) question ="مالذي اصطادوه في الرحلة؟";
        else if (num == 5) question ="كيف عادوا الى المنزل؟";
        
    } else if (currentPhonemeNum == 11) {
        
        if (num == 1) question ="الى أين ذهب سمير ووالده ووالدته؟";
        else if (num == 2) question ="من هو ملك الحيوانات؟";
        else if (num == 3) question ="ماذا تاكل القرود؟";
        else if (num == 4) question ="ماذا يأكل الفيل؟";
        else if (num == 5) question ="ماذا يأكل كلب البحر؟";
        
    } else if (currentPhonemeNum == 12) {
        
        if (num == 1) question = "ماذا تحب ريما؟";
        else if (num == 2) question = "ما هو لون الكلب؟";
        else if (num == 3) question = "بماذا شعرت ريما حين ضاع الكلب؟";
        else if (num == 4) question = "من من طلبت ريما المساعدة؟";
        else if (num == 5) question = "أين وجد ابوها الكلب؟";
        
    }
    
    return question;
}

string OPTextProvider::getStory() {

    string story = "";
    
    if (currentPhonemeNum == 1) {
        story = "عادل عنده كتاب جديد، فيه دروس مفيدة، وقصص مسلية وصور جميلة، وله غلاف نظيف وجميل. عادل يحب كتابه ويحافظ عليه جيداً";
    } else if (currentPhonemeNum == 2) {
        story = "القرية فيها منازل قليلة، وشوارع ضيقة، وبيوت صغيرة، مبنية من الطين، ويسكنها الفلاحون، ويوجد حولها حقول ومزارع كبيرة، وأهل القرية لطفاء ويحبون اكرام الضيف";
    } else if (currentPhonemeNum == 3) {
        story = "دخل اللص الى المنزل ليسرق مافيه، وكان الوقت ليلا، رَآه الكلب فأخذ ينبح نباحا شديدا، فاستيقظ سكان البيت وهرب اللص خائف مرعوب";
    } else if (currentPhonemeNum == 4) {
        story = "يحتاج الانسان الى غذاء جيد، ليحافظ على صحته، ويزوده بالقوة والقدرة على العمل، ويتكون غذاء الانسان من لحم وخضار ودهن وبيض وفاكهة، من لا يتناول الغذاء الجيد سيُصبِح جسمه ضعيفا وسيصاب بالامراض";
    } else if (currentPhonemeNum == 5) {
        story = "النحلة حشرة عجيبة، تعيش في جماعات متعاونة، وللنحلة أربعة اجنحة خفيفة حريرية، تسمح لها ان تنتقل من ثمرة الى ثمرة ومن زهرة الى زهرة، ثم تخرج لنا عسل حلو بألوان مختلفة يشفي الانسان من الامراض";
    } else if (currentPhonemeNum == 6) {
        story = "قضيت عطلة الصيف في بيت جدي، في قرية صغيرة، كنت اخرج في الصباح وأتمشى على الطريق الزراعي واقطف الزهور، والعب مع الحيوانات ، ثم اعود وأتناول الحلوى اللذيذة التي صنعتها لي جدتي";
    } else if (currentPhonemeNum == 7) {
        story = "كريم عنده كرة جميلة، يحبها ويحافظ عليها ويحملها بيديه، ويضربها بقدمه فتذهب بعيدا، يلعب بها مع اخوته وأصدقاءه في الملعب الكبير، كريم يريد ان يصبح لاعبا مشهورا عندما يكبر";
    } else if (currentPhonemeNum == 8) {
        story = "باسم ولد نشيط، يستيقظ كل يوم ويغسل وجهه بالماء والصابون ويرتب سريره وملابسه وينظف غرفته، ثم يذهب ويساعد والده في عمله ويحمل معه الخضار ويوصلها الى البيت ثم يحضر دروسه ويساعد والدته في تحضير العشاء";
    } else if (currentPhonemeNum == 9) {
        story = "طارق طفل صغير، في الصف الاول، شاهد في حديقة منزلهم الطيور تحط على الشجرة وتغرد، متسلق الشجرة ليمسك بالطيور ولكنه سقط على الارض وكسر يده، أسرع والده وحمله وذهب به الى المستشفى، جاء الطبيب وعالج يده";
    } else if (currentPhonemeNum == 10) {
        story = "ذهب خالد مع ابيه في رحلة لصيد السمك، احضروا معهم كل أدوات الصيد والطعم للأسماك، وجهزوا بعض الطعام والشراب واحضروا أيضا مصابيح الإضاءة ولَم ينسوا سترة النجاة، قضوا وقتا ممتعا واصطادوا الكثير من الأسماك ثم عادوا فرحين الى المنزل";
    } else if (currentPhonemeNum == 11) {
        story = "ذهب سمير ووالده ووالدته الى حديقة الحيوان، وفيها شاهد الأسد ملك الحيوانات والدب والنمر، ثم اتجه الى أقفاص القرود فرآها تالك الموز، ورآى أيضا الفيل  وهو يرفع خرطومه ويأكل البرسيم، ثم رآى كلب البحر وهو يأكل السمك من يد الحارس وشاهد الزرافة والحمار الوحشي وبعض الزواحف والطيور ثم عاد الى منزله مسرورا";
    } else if (currentPhonemeNum == 12) {
        story = "ريما فتاة صغيرة تحب الحيوانات، لديها كلب صغير لونه ابيض، تأخذه كل يوم وتتنزه في الحديقة، خرج الكلب ذات يوم بمفرده وضاع ولَم يستطع ان يعود، حزنت ريما كثيرا وطلبت من والدها ان يساعدها لتجد كلبها، خرج ابوها من البيت وبحث عن الكلب فوجده في الحديقة الكبيرة بجانب البيت فأحضره معه، فرحت ريما كثيرا وشكرت والدها";
    }

    return story;

}

