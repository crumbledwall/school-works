<template>
  <div class="cover">
    <router-link :to="{ path: '/details', query: { url: encodeURIComponent(imgsrc), name: encodeURIComponent(imgalt), detail: encodeURIComponent(imgdetail) }}">
    <img class="coverimg" v-bind:src="imgsrc" v-bind:alt="imgalt">
    <div class="bookss">
      {{ imgalt }}
    </div></router-link>
  </div>
</template>


<script>
export default {
    name: "Cover",
    props:{
        imgsrc: String,
        imgalt: String,
        imgdetail: String
    }
  }
</script>

<style>
.cover:hover img{
  opacity: 0;
  filter: alpha(opacity=0);
}
img{
  max-height: 250px;
  display: block;
  object-fit: cover;
  display: block;
  position: relative;
  max-width: none;
  margin: 0 auto;
  width: 400px;
  height: 250px;
  background-position: center center;
  background-repeat: no-repeat;
  -webkit-transition: opacity 0.35s, -webkit-transform 0.35s;
  transition: opacity 0.35s, transform 0.35s;
  -webkit-backface-visibility: hidden;
  backface-visibility: hidden;
}
.cover:hover .bookss{
  opacity: 1;
  filter: alpha(opacity=100);
}

</style>