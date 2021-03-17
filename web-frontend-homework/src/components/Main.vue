<template>
  <div class="block">
    <el-carousel trigger="click" height="380px" class="carousel">
      <el-carousel-item v-for="item in imgData" :key="item.url">
      <img style="max-height:380px;height:380px;width:auto;" :src="item.url"/>
      </el-carousel-item>
    </el-carousel>
    <div class="art-block"><p class="art">境の長いトンネルを抜けると雪国であった。夜の底が白くなった。信号所に汽車が止まった。<br>内側の座席から娘が立って来て、島村の前のガラス窓を落とした。雪の冷気が流れ込んだ。</p>
  </div></div>
</template>



<script>
export default {
  name: 'Main',
  data(){
    return{
      imgData: [
        {
          "url": require("../assets/unsplash1.jpg")
        },
        {
          "url": require("../assets/unsplash2.jpg")
        },
        {
          "url": require("../assets/unsplash3.jpg")
        },
        {
          "url": require("../assets/unsplash4.jpg")
        },
        {
          "url": require("../assets/unsplash5.jpg")
        }
      ]
    }
  }
}
</script>

<style scoped>

  .block{
    width:600px;
    padding-top:90px;
    margin: 0 auto;
    
  }
  .art{
    writing-mode: vertical-rl;
    writing-mode: tb-lr;
    margin: 0 auto;
    font-size: 22px;
    text-align: start;
  }
  .art-block{
    width: 600px;
    height: 200px;
    padding-top:80px;
    position: relative;
  }
</style>
