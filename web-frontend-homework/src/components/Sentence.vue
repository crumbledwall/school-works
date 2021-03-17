<template>
  <div class="bookdetail">
    <div class="bookname">
    <img :src="decodeURIComponent($route.query.url)" class="imgshow">
      《{{ decodeURIComponent($route.query.name) }}》  
    </div>
    <div class="Sentence">
      {{ decodeURIComponent($route.query.detail) }}
    </div>
  </div>
</template>

<script>
export default {
    name: "Sentence"
  }
</script>

<style scoped>
  .imgshow{
    width: 400px;
  }
  .Sentence{
    width: 400px;
    height: 300px;
    text-indent: 3px;
    line-height: 25px;
    margin-top: 90px;
    font-size: 18px;
    line-height: 40px;
    border:1.5px solid rgba(189, 184, 184, 0.582);
    border-radius: 9px;
    padding: 12px;
    margin-bottom: 50px;
  }
  .bookdetail{
    margin: 0 auto;
    width: 600px;
    display: flex;
    height: 300px;
    flex-direction: column;
    align-items: center;
    margin-bottom: 50px;
  }
  .bookname{
    margin-top: 140px;
    width: 400px;
    left: 0;
  }
</style>